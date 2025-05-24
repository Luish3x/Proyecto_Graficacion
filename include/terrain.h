// terrain.h
#pragma once
#include <vector>

using HeightMap = std::vector<std::vector<int>>;

HeightMap generateHeightMap(int size, float roughness);

