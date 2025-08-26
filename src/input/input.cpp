// input.cpp
// Centralizes SDL event processing and maps it to RenderState mutations.
#include <SDL2/SDL.h>
#include "input.h"
#include "../app_state/app_state.h"
#include "../3d_renderer/3d_renderer.h"

// A single global helper is sufficient to construct primitives on demand.
static Objects3d g_objects3d;

bool handleEvent(RenderState *state, const SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        state->running = false;
        return true;
    }

    if (event.type == SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            state->screenWidth = event.window.data1;
            state->screenHeight = event.window.data2;
            return true;
        }
    }

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            state->running = false;
            return true;
        case SDLK_1:    // top-row '1'
        case SDLK_KP_1: // keypad '1'
        case SDLK_c:
            g_objects3d.makeCube(*state, 1, 255, 0, 0);
            return true;
        case SDLK_2:    // top-row '2'
        case SDLK_KP_2: // keypad '2'
        case SDLK_p:
            g_objects3d.makePyramid(*state, 1, 0, 0, 255);
            return true;
        default:
            break;
        }
    }

    return false;
}