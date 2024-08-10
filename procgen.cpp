#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const int NUM_SEEDS = 10;

struct Biome {
    char symbol;
    int terrainType; 
    int colorCode;   
};

float distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void setTextColor(int colorCode) {
    std::cout << "\x1B[3" << colorCode << "m";
}

void resetTextColor() {
    std::cout << "\x1B[0m";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::vector<std::vector<Biome>> map(MAP_HEIGHT, std::vector<Biome>(MAP_WIDTH));

    std::vector<std::pair<int, int>> seeds;
    for (int i = 0; i < NUM_SEEDS; ++i) {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;
        seeds.emplace_back(x, y);
    }

    std::vector<Biome> biomes;
    biomes.push_back({'F', 0, 2}); // Forest (Green text)
    biomes.push_back({'D', 1, 3}); // Desert (Yellow text)
    biomes.push_back({'M', 2, 4}); // Mountains (Blue text)
    // Add more biomes as needed

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int nearestSeedIndex = 0;
            float minDistance = distance(x, y, seeds[0].first, seeds[0].second);

            for (int i = 1; i < NUM_SEEDS; ++i) {
                float d = distance(x, y, seeds[i].first, seeds[i].second);
                if (d < minDistance) {
                    nearestSeedIndex = i;
                    minDistance = d;
                }
            }

            map[y][x] = biomes[nearestSeedIndex];
        }
    }

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            setTextColor(map[y][x].colorCode); // Set text color
            std::cout << map[y][x].symbol << ' ';
            resetTextColor(); // Reset text color to default
        }
        std::cout << std::endl;
    }

    std::cout << "Press any key to exit..." << std::endl;
    _getch(); // Wait for a key press

    return 0;
}
