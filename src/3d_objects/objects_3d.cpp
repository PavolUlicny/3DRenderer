// objects_3d.cpp
// Implementation of simple wireframe primitives: cube, pyramid.

#include "objects_3d.h"
#include <utility>
#include <vector>

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
