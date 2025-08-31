/**
 * @file objects_3d.h
 * @brief Helpers to populate RenderState with simple 3D primitives.
 */
#pragma once

#include "../app_state/app_state.h" // Point3d, Edge3d, RenderState

/**
 * @brief Factory for basic wireframe objects (cube, pyramid).
 *
 * Populates the provided RenderState's basePoints3d and edges3d with
 * vertices and colored edges for each primitive, centered at the origin.
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
     * @param state Target render state to receive vertices and edges.
     * @param size  Half-extent of the base; apex is at +Z with the same size.
     * @param red   Edge/vertex color (0..255).
     * @param green Edge/vertex color (0..255).
     * @param blue  Edge/vertex color (0..255).
     */
    void makePyramid(RenderState &state, float size, int red, int green, int blue);
};
