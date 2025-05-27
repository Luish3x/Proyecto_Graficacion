#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void diamondSquare(int Array[CHUNK_X][CHUNK_Z], int size)
{
 int half = size / 2;
 if (half < 1)
  return ;//square steps
 for (int z = half; z < CHUNK_Z; z+=size)
  for (int x = half; x < CHUNK_X; x+=size)
   squareStep(Array, x % CHUNK_X, z % CHUNK_Z, half);// diamond steps
 int col = 0;
 for (int x = 0; x < CHUNK_X; x += half)
 {
  col++;
  //If this is an odd column.
  if (col % 2 == 1)
   for (int z = half; z < CHUNK_Z; z += size)
    diamondStep(Array, x % CHUNK_X, z % CHUNK_Z, half);
  else
   for (int z = 0; z < CHUNK_Z; z += size)
    diamondStep(Array, x % CHUNK_X, z % CHUNK_Z, half);
 }
 diamondSquare(Array, size / 2);
}

void squareStep(int Array[CHUNK_X][CHUNK_Z], int x, int z, int reach)
{
 int count = 0;
 float avg = 0.0f;
 if (x - reach >= 0 && z - reach >= 0)
 {
  avg += Array[x-reach][z-reach];
  count++;
 }
 if (x - reach >= 0 && z + reach < CHUNK_Z)
 {
  avg += Array[x-reach][z+reach];
  count++;
 }
 if (x + reach < CHUNK_X && z - reach >= 0)
 {
  avg += Array[x+reach][z-reach];
  count++;
 }
 if (x + reach < CHUNK_X && z + reach < CHUNK_Z)
 {
  avg += Array[x+reach][z+reach];
  count++;
 }
 avg += random(reach);
 avg /= count;
 Array[x][z] = round(avg);
}

void diamondStep(int Array[CHUNK_X][CHUNK_Z], int x, int z, int reach)
{
 int count = 0;
 float avg = 0.0f;
 if (x - reach >= 0)
 {
  avg += Array[x-reach][z];
  count++;
 }
 if (x + reach < CHUNK_X)
 {
  avg += Array[x+reach][z];
  count++;
 }
 if (z - reach >= 0)
 {
  avg += Array[x][z-reach];
  count++;
 }
 if (z + reach < CHUNK_Z)
 {
  avg += Array[x][z+reach];
  count++;
 } avg += random(reach);
 avg /= count;
 Array[x][z] = (int)avg;
}

inline static float random(int range)
{
 return (rand() % (range * 2)) - range;
}

void printHeightmap(const std::vector<std::vector<int>>& heightmap) {
    for (const auto& row : heightmap) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    std::srand(std::time(0));

    const int size = 33; // 2^3 + 1
    const int roughness = 32;

    std::vector<std::vector<int>> heightmap(size, std::vector<int>(size, 0));

    // Inicializar esquinas
    heightmap[0][0] = std::rand() % 100;
    heightmap[0][size - 1] = std::rand() % 100;
    heightmap[size - 1][0] = std::rand() % 100;
    heightmap[size - 1][size - 1] = std::rand() % 100;

    diamondSquare(heightmap, size, roughness);

    printHeightmap(heightmap);

    return 0;
}

