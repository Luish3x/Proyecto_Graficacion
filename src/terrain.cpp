// terrain.cpp
#include "terrain.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

float randFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

void diamondStep(HeightMap& map, int x, int y, int size, float offset) {
    int half = size / 2;
    float avg = (map[x][y] + map[x + size][y] + map[x][y + size] + map[x + size][y + size]) / 4.0f;
    map[x + half][y + half] = avg + randFloat(-offset, offset);
}

void squareStep(HeightMap& map, int x, int y, int step, float offset) {
    int count = 0;
    float sum = 0;
    if (x - step >= 0) { sum += map[x - step][y]; count++; }
    if (x + step < map.size()) { sum += map[x + step][y]; count++; }
    if (y - step >= 0) { sum += map[x][y - step]; count++; }
    if (y + step < map.size()) { sum += map[x][y + step]; count++; }
    map[x][y] = (sum / count) + randFloat(-offset, offset);
}

HeightMap generateHeightMap(int size, float roughness) {
    srand(time(nullptr));
    HeightMap map(size, std::vector<int>(size, 0));

    map[0][0] = rand() % 10;
    map[0][size - 1] = rand() % 10;
    map[size - 1][0] = rand() % 10;
    map[size - 1][size - 1] = rand() % 10;

    int step = size - 1;
    float scale = roughness;

    while (step > 1) {
        int half = step / 2;

        // Diamond step
        for (int x = 0; x < size - 1; x += step) {
            for (int y = 0; y < size - 1; y += step) {
                diamondStep(map, x, y, step, scale);
            }
        }

        // Square step
        for (int x = 0; x < size; x += half) {
            for (int y = (x + half) % step; y < size; y += step) {
                squareStep(map, x, y, half, scale);
            }
        }

        step /= 2;
        scale *= roughness;
    }

    return map;
}

