// 3d_renderer.cpp
// Simple 3D wireframe helpers that rotate, project, and draw using SDL2.
// Responsibilities:
//  - rotation around X/Y/Z
//  - perspective projection
//  - per-frame callback that animates and renders the current object

#include <SDL2/SDL.h>
#include "../3d_renderer/3d_renderer.h"
#include "../input/input.h"
#include <algorithm>
#include <vector>
#include <cmath>

constexpr float PI_F = 3.14159265358979323846f;

// Renderer3d implementations
// --------------------------
/** Project a 3D point into screen space with a small guard to avoid
 * extreme values when denominator approaches zero. */
Point2d Renderer3d::projectPoint(const Point3d &point3d, float focalLength, float viewerDistance, int screenWidth, int screenHeight)
{
    Point2d point2d;
    float denominator = (viewerDistance + point3d.z);
    // Guard against division by very small numbers which can explode coordinates
    if (std::fabs(denominator) < 1e-3f)
    {
        denominator = (denominator >= 0.0f) ? 1e-3f : -1e-3f;
    }
    point2d.x = screenWidth * 0.5f + (focalLength * point3d.x) / denominator;
    point2d.y = screenHeight * 0.5f - (focalLength * point3d.y) / denominator;
    point2d.red = point3d.red;
    point2d.green = point3d.green;
    point2d.blue = point3d.blue;
    return point2d;
}

/** Rotate a point around the X axis by angleDegrees. */
Point3d Renderer3d::rotateX(const Point3d &point3d, float angleDegrees)
{
    float angleRadians = angleDegrees * PI_F / 180.0f;
    float y = point3d.y * cos(angleRadians) - point3d.z * sin(angleRadians);
    float z = point3d.y * sin(angleRadians) + point3d.z * cos(angleRadians);
    return {point3d.x, y, z, point3d.red, point3d.green, point3d.blue};
}

/** Rotate a point around the Y axis by angleDegrees. */
Point3d Renderer3d::rotateY(const Point3d &point3d, float angleDegrees)
{
    float angleRadians = angleDegrees * PI_F / 180.0f;
    float x = point3d.x * cos(angleRadians) + point3d.z * sin(angleRadians);
    float z = -point3d.x * sin(angleRadians) + point3d.z * cos(angleRadians);
    return {x, point3d.y, z, point3d.red, point3d.green, point3d.blue};
}

/** Rotate a point around the Z axis by angleDegrees. */
Point3d Renderer3d::rotateZ(const Point3d &point3d, float angleDegrees)
{
    float angleRad = angleDegrees * PI_F / 180.0f;
    float x = point3d.x * cos(angleRad) - point3d.y * sin(angleRad);
    float y = point3d.x * sin(angleRad) + point3d.y * cos(angleRad);
    return {x, y, point3d.z, point3d.red, point3d.green, point3d.blue};
}

// Objects3d implementations
// -------------------------
/** Populate state with a unit cube scaled by 'size' and colored edges. */
void Objects3d::makeCube(RenderState &state, float size, int red, int green, int blue)
{
    state.basePoints3d.clear();
    state.edges3d.clear();

    std::vector<Point3d> points3d = {
        {-size, -size, -size, red, green, blue},
        {size, -size, -size, red, green, blue},
        {size, size, -size, red, green, blue},
        {-size, size, -size, red, green, blue},
        {-size, -size, size, red, green, blue},
        {size, -size, size, red, green, blue},
        {size, size, size, red, green, blue},
        {-size, size, size, red, green, blue}};

    std::vector<Edge3d> edges3d = {
        {0, 1, red, green, blue},
        {1, 2, red, green, blue},
        {2, 3, red, green, blue},
        {3, 0, red, green, blue},
        {4, 5, red, green, blue},
        {5, 6, red, green, blue},
        {6, 7, red, green, blue},
        {7, 4, red, green, blue},
        {0, 4, red, green, blue},
        {1, 5, red, green, blue},
        {2, 6, red, green, blue},
        {3, 7, red, green, blue}};

    state.basePoints3d = std::move(points3d);
    state.edges3d = std::move(edges3d);
}

/** Populate state with a square-based pyramid scaled by 'size'. */
void Objects3d::makePyramid(RenderState &state, float size, int red, int green, int blue)
{
    state.basePoints3d.clear();
    state.edges3d.clear();

    std::vector<Point3d> points3d = {
        {-size, -size, -size, red, green, blue},
        {size, -size, -size, red, green, blue},
        {size, size, -size, red, green, blue},
        {-size, size, -size, red, green, blue},
        {0.0f, 0.0f, size, red, green, blue},
    };

    std::vector<Edge3d> edges3d = {
        {0, 1, red, green, blue},
        {1, 2, red, green, blue},
        {2, 3, red, green, blue},
        {3, 0, red, green, blue},
        {0, 4, red, green, blue},
        {1, 4, red, green, blue},
        {2, 4, red, green, blue},
        {3, 4, red, green, blue}};

    state.basePoints3d = std::move(points3d);
    state.edges3d = std::move(edges3d);
}

// Frame callback
// --------------
// Advances rotation using measured delta time, projects the current vertices
// to 2D, and draws points and edges using SDL_Renderer.
void frame_callback(SDL_Window *, SDL_Renderer *renderer, void *userData)
{

    auto *state = static_cast<RenderState *>(userData);
    Renderer3d renderer3d;

    // Input handled in the main event loop within renderer_run

    // Compute delta time (seconds) using SDL high-resolution timer
    const Uint64 currentPerformanceCounter = SDL_GetPerformanceCounter();
    const Uint64 performanceCounterFrequency = SDL_GetPerformanceFrequency();
    float deltaSeconds = 0.0f;
    if (state->lastPerformanceCounter != 0 && performanceCounterFrequency != 0)
    {
        deltaSeconds = static_cast<float>(static_cast<double>(currentPerformanceCounter - state->lastPerformanceCounter) / static_cast<double>(performanceCounterFrequency));
        // Clamp to avoid huge jumps after pauses/window moves
        if (deltaSeconds > 0.1f)
            deltaSeconds = 0.1f;
    }
    state->lastPerformanceCounter = currentPerformanceCounter;

    // Rotate in degrees per second
    state->angleX += state->rotateSpeedX * deltaSeconds;
    state->angleY += state->rotateSpeedY * deltaSeconds;
    state->angleZ += state->rotateSpeedZ * deltaSeconds;

    // Keep angles in [0, 360) to avoid growing unbounded values
    auto wrap360 = [](float a)
    {
        while (a >= 360.0f)
        {
            a -= 360.0f;
        }

        while (a < 0.0f)
        {
            a += 360.0f;
        }

        return a;
    };
    state->angleX = wrap360(state->angleX);
    state->angleY = wrap360(state->angleY);
    state->angleZ = wrap360(state->angleZ);

    std::vector<Point3d> rotatedPoints3d;
    rotatedPoints3d.reserve(state->basePoints3d.size());
    for (const auto &point3d : state->basePoints3d)
    {
        Point3d rotatedPoint = point3d;
        rotatedPoint = renderer3d.rotateY(rotatedPoint, state->angleY);
        rotatedPoint = renderer3d.rotateX(rotatedPoint, state->angleX);
        rotatedPoint = renderer3d.rotateZ(rotatedPoint, state->angleZ);
        rotatedPoints3d.push_back(rotatedPoint);
    }

    std::vector<Point2d> projectedPoints2d;
    projectedPoints2d.reserve(rotatedPoints3d.size());
    for (const auto &vertex : rotatedPoints3d)
    {
        projectedPoints2d.push_back(renderer3d.projectPoint(vertex, state->focalLength, state->viewerDistance, state->screenWidth, state->screenHeight));
    }

    for (const auto &projectedPoint : projectedPoints2d)
    {
        SDL_SetRenderDrawColor(renderer, projectedPoint.red, projectedPoint.green, projectedPoint.blue, 255);
        SDL_RenderDrawPoint(renderer, static_cast<int>(projectedPoint.x), static_cast<int>(projectedPoint.y));
    }

    for (const auto &edge : state->edges3d)
    {
        if (edge.pointOneIndex < 0 || edge.pointTwoIndex < 0)
            continue;
        if (static_cast<size_t>(edge.pointOneIndex) >= projectedPoints2d.size() ||
            static_cast<size_t>(edge.pointTwoIndex) >= projectedPoints2d.size())
            continue;

        const auto &pointOne = projectedPoints2d[edge.pointOneIndex];
        const auto &pointTwo = projectedPoints2d[edge.pointTwoIndex];
        SDL_SetRenderDrawColor(renderer, edge.red, edge.green, edge.blue, 255);
        SDL_RenderDrawLine(renderer, static_cast<int>(pointOne.x), static_cast<int>(pointOne.y), static_cast<int>(pointTwo.x), static_cast<int>(pointTwo.y));
    }
}