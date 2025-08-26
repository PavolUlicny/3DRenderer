// main.cpp
// Demo entry point: initializes RenderState, selects a primitive, and launches
// the SDL-driven render loop.
#include "3d_renderer/3d_renderer.h"
#include "app_state/app_state.h"

/**
 * @brief Program entry: configures the scene and starts the renderer.
 */
int main()
{
    RenderState state;
    Objects3d objects3d;

    state.screenWidth = 1000;
    state.screenHeight = 1000;

    // Projection parameters (tweak to change perspective strength)
    state.focalLength = 100000.0f;
    state.viewerDistance = 500.0f;

    // Angular velocities (deg/sec)
    state.rotateSpeedX = 50;
    state.rotateSpeedY = -25;
    state.rotateSpeedZ = 10;

    objects3d.makeCube(state, 1.0f, 255, 0, 0);

    // Enter the render loop; returns 0 on normal shutdown
    return renderer_run("3D Renderer Demo", state.screenWidth, state.screenHeight, frame_callback, &state);
}