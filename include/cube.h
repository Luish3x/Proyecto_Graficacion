// cube.h
#pragma once
#include <vector>
#include <glm/glm.hpp>

enum Face { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };

std::vector<float> getCubeFaceVertices(glm::vec3 position, Face face);

