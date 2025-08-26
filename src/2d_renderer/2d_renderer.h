/**
 * @file 2d_renderer.h
 * @brief Minimal SDL2 rendering loop Abstraction.
 *
 * Exposes a single entry point that owns the SDL window and renderer and
 * invokes a user-supplied frame callback every iteration of the loop.
 */
#pragma once

#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Per-frame callback invoked by the render loop.
     *
     * Called once per frame after the backbuffer is cleared and before present.
     * Use the provided SDL_Renderer to issue draw calls for that frame.
     *
     * @param window   SDL window handle (owned by the loop).
     * @param renderer SDL renderer handle (owned by the loop).
     * @param userData Opaque pointer passed through unchanged to allow stateful rendering.
     */
    typedef void (*RendererFrameCallback)(SDL_Window *window, SDL_Renderer *renderer, void *userData);

    /**
     * @brief Run the SDL window/render loop until a quit condition is met.
     *
     * The function initializes SDL (video subsystem), creates a centered window
     * and a VSync-enabled accelerated renderer, then repeatedly:
     *  - polls and dispatches SDL events,
     *  - clears the backbuffer,
     *  - calls the supplied frame callback,
     *  - presents the backbuffer.
     *
     * The loop terminates when the userData-provided state indicates shutdown
     * (e.g., RenderState::running is false) or when a fatal SDL error occurs.
     *
     * @param title     Window title (UTF-8). If null, a default is used.
     * @param width     Desired window width in pixels (fallback to 800 if <= 0).
     * @param height    Desired window height in pixels (fallback to 600 if <= 0).
     * @param on_frame  User callback invoked once per frame.
     * @param userData  Opaque pointer given to the callback.
     * @return int      0 on normal shutdown, non-zero on initialization error.
     */
    int renderer_run(const char *title, int width, int height, RendererFrameCallback on_frame, void *userData);

#ifdef __cplusplus
}
#endif
