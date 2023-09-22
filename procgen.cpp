#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h> // Include this for _getch() function

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const int NUM_SEEDS = 10;

// Define a structure to represent a biome
struct Biome {
    char symbol;
    int terrainType; // You can use an enum for terrain types
    int colorCode;   // ANSI color code (0-7)
};

// Function to calculate the distance between two points
float distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Function to set text color using ANSI escape codes
void setTextColor(int colorCode) {
    std::cout << "\x1B[3" << colorCode << "m";
}

// Function to reset text color to default
void resetTextColor() {
    std::cout << "\x1B[0m";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Create a map
    std::vector<std::vector<Biome>> map(MAP_HEIGHT, std::vector<Biome>(MAP_WIDTH));

    // Generate random seed points
    std::vector<std::pair<int, int>> seeds;
    for (int i = 0; i < NUM_SEEDS; ++i) {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;
        seeds.emplace_back(x, y);
    }

    // Define biomes and assign them to seed points with color codes
    std::vector<Biome> biomes;
    biomes.push_back({'F', 0, 2}); // Forest (Green text)
    biomes.push_back({'D', 1, 3}); // Desert (Yellow text)
    biomes.push_back({'M', 2, 4}); // Mountains (Blue text)
    // Add more biomes as needed

    // Generate the map based on Voronoi-like regions
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int nearestSeedIndex = 0;
            float minDistance = distance(x, y, seeds[0].first, seeds[0].second);

            // Find the nearest seed point
            for (int i = 1; i < NUM_SEEDS; ++i) {
                float d = distance(x, y, seeds[i].first, seeds[i].second);
                if (d < minDistance) {
                    nearestSeedIndex = i;
                    minDistance = d;
                }
            }

            // Assign a biome to the cell based on the nearest seed
            map[y][x] = biomes[nearestSeedIndex];
        }
    }

    // Print the generated map with colored text
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
