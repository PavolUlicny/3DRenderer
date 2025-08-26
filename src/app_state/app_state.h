/**
 * @file app_state.h
 * @brief Shared data types and render/application state.
 */
#pragma once
#include <vector>
#include <cstdint>

/**
 * @brief A 3D point with per-vertex RGB color in integer 0..255.
 */
struct Point3d
{
    float x, y, z;        ///< 3d coordinates in world space
    int red, green, blue; ///< Per-vertex color components
};

/**
 * @brief A projected 2D point on the screen with per-vertex color.
 */
struct Point2d
{
    float x, y;           ///< Screen-space coordinates in pixels
    int red, green, blue; ///< Color used for drawing the point
};

/**
 * @brief A colored edge connecting two vertex indices.
 */
struct Edge3d
{
    int pointOneIndex, pointTwoIndex; ///< Indices into the vertex array
    int red, green, blue;             ///< Edge color
};

/**
 * @brief Mutable render/application state used across modules.
 */
struct RenderState
{
    // Geometry definition (object space)
    std::vector<Point3d> basePoints3d; ///< Base vertices before rotation
    std::vector<Edge3d> edges3d;       ///< Edges defined by vertex indices

    // Camera / projection parameters
    float focalLength = 100000.0f; ///< Perspective scale factor
    float viewerDistance = 500.0f; ///< Distance from camera to origin

    // Backbuffer dimensions (updated on window resize)
    int screenWidth = 800;
    int screenHeight = 600;

    // Rotation speeds (degrees per second)
    float rotateSpeedX = 0.0f;
    float rotateSpeedY = 0.0f;
    float rotateSpeedZ = 0.0f;

    // Current rotation angles (degrees)
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;

    // Lifecycle
    bool running = true; ///< Main loop flag

    // Timing (SDL high-resolution counters)
    std::uint64_t lastPerformanceCounter = 0; ///< For delta time calculation
};