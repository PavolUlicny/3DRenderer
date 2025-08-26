/**
 * @file input.h
 * @brief Translates SDL events into application state changes.
 */
#pragma once
#include "../app_state/app_state.h"
#include <SDL2/SDL.h>

/**
 * @brief Process a single SDL_Event and mutate RenderState appropriately.
 *
 * Handled events:
 *  - SDL_QUIT: sets running = false
 *  - SDL_WINDOWEVENT_RESIZED / SIZE_CHANGED: update screenWidth/Height
 *  - SDL_KEYDOWN:
 *      Esc: quit
 *      C:   create cube primitive
 *      P:   create pyramid primitive
 *      Left/Right: tweak Y rotation angle
 *
 * @param state Mutable application state
 * @param event SDL event to handle
 * @return true if the event was recognized and handled, false otherwise
 */
bool handleEvent(RenderState *state, const SDL_Event &event);