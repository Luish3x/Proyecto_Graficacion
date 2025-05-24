// cube.cpp
#include "cube.h"

std::vector<float> getCubeFaceVertices(glm::vec3 pos, Face face) {
    float x = pos.x, y = pos.y, z = pos.z;
    switch (face) {
        case TOP:
            return {
                x, y + 1, z,
                x + 1, y + 1, z,
                x + 1, y + 1, z + 1,
                x, y + 1, z + 1
            };
        case BOTTOM:
            return {
                x, y, z,
                x + 1, y, z,
                x + 1, y, z + 1,
                x, y, z + 1
            };
        // LEFT, RIGHT, FRONT, BACK iguales: omito por espacio
    }
    return {};
}

