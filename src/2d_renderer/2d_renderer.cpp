//
// 2d_renderer.cpp
// Implements a small SDL2-driven render loop that owns the window and renderer.
// The loop delegates input processing to handleEvent() and rendering to a
// user-provided frame callback.
//
// Lifetime:
//  - SDL is initialized on entry and cleaned up on exit
//  - SDL_Window and SDL_Renderer are created once and destroyed after the loop
//  - The loop runs while the provided user state indicates 'running == true'
//
#define SDL_MAIN_HANDLED
#include "../2d_renderer/2d_renderer.h"
#include "../app_state/app_state.h"
#include "../input/input.h"

// Runs the SDL renderer
int renderer_run(const char *title, int width, int height, RendererFrameCallback on_frame, void *userData)
{
    // Inform SDL that we manage the main() entry point ourselves
    SDL_SetMainReady();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // Request higher quality texture filtering when scaling
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create the centered window with the specified title and dimensions
    SDL_Window *window = SDL_CreateWindow(title ? title : "3D Renderer",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width > 0 ? width : 800,
                                          height > 0 ? height : 600,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Check if the window was created successfully
    if (!window)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an accelerated renderer with VSync enabled when available
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Check if the renderer was created successfully
    if (!renderer)
    {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // The application-specific state is carried through userData
    RenderState *state = static_cast<RenderState *>(userData);

    // Main loop
    while (state->running)
    {
        // Handle events (input.cpp translates events into state changes)
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            handleEvent(state, event);
        }

        // Set the render color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the frame (issue all draw calls through the callback)
        if (on_frame)
        {
            on_frame(window, renderer, userData);
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Shutdown renderer
    SDL_DestroyRenderer(renderer);

    // Shutdown window
    SDL_DestroyWindow(window);

    // Shutdown SDL video subsystem
    SDL_Quit();

    return 0;
}