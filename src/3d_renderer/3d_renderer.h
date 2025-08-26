// Header for simple 3D wireframe renderer using SDL2
// Declares Renderer3d, Objects3d, and the frame callback

#pragma once

#include "../2d_renderer/2d_renderer.h" // Point2d, Point3d
#include "../app_state/app_state.h"     // RenderState, Edge3d

// Forward declarations to avoid pulling in SDL headers here
struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief Math utilities to rotate and project 3D points to 2D.
 */
class Renderer3d
{
public:
    /**
     * @brief Perspective-project a 3D point onto the 2D screen.
     * @param point3d        Point in world/object space.
     * @param focalLength    Perspective scale factor (higher => less distortion).
     * @param viewerDistance Distance from the camera to origin; used as z-offset.
     * @param screenWidth    Current backbuffer width.
     * @param screenHeight   Current backbuffer height.
     * @return Point2d       Projected 2D point with the original color.
     */
    Point2d projectPoint(const Point3d &point3d, float focalLength, float viewerDistance, int screenWidth, int screenHeight);

    /** Rotate around the X axis by angle in degrees. */
    Point3d rotateX(const Point3d &point3d, float angleDegrees);
    /** Rotate around the Y axis by angle in degrees. */
    Point3d rotateY(const Point3d &point3d, float angleDegrees);
    /** Rotate around the Z axis by angle in degrees. */
    Point3d rotateZ(const Point3d &point3d, float angleDegrees);
};

/**
 * @brief Helpers to populate RenderState with simple primitives.
 */
class Objects3d
{
public:
    /**
     * @brief Generate a colored cube centered at the origin.
     * @param state Target render state to receive vertices and edges.
     * @param size  Half-extent of the cube along each axis.
     * @param red   Edge/vertex color (0..255).
     * @param green Edge/vertex color (0..255).
     * @param blue  Edge/vertex color (0..255).
     */
    void makeCube(RenderState &state, float size, int red, int green, int blue);
    /**
     * @brief Generate a 4-sided pyramid with square base centered at origin.
     */
    void makePyramid(RenderState &state, float size, int red, int green, int blue);
};

/**
 * @brief Per-frame render callback used by the application.
 *
 * Computes rotation based on delta time, projects 3D vertices, and draws
 * points and edges using SDL_Renderer. Input handling occurs outside of this
 * function in the main render loop (2d_renderer.cpp).
 */
void frame_callback(SDL_Window *, SDL_Renderer *renderer, void *userData);
