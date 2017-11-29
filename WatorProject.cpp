/** Copyright 2017 Karl Redmond, Ger Dobbs
 *ProducerConsumerMain.cpp
 *Author: 	Karl Redmond, Ger Dobbs
 *Date:   	Thursday,  27 November 2017.
 *License:	GNU General Public License v3.0
 *Brief:	Joint 4th Year Wator simulation Project
**/

#include <iostream>
#include <random>

int const OCEANSIZEX = 10;
int const OCEANSIZEY = 10;
int numFish = 2;
int numShark = 5;
int fishBreedTime = 3;
int sharkBreedTime = 8;
int sharkStarveTime = 4;
char ocean[OCEANSIZEX][OCEANSIZEY][3];
int xPos, yPos;

/**
 * \brief Initialize 3 Dimensional Cube. The first layer [0] represents what will be displayed.
 * The second layer [1] represents the breed time for the fish and sharks that exist in layer [0].
 * The third layer[2] represents the starve time for the sharks that exist in layer[0].
 */
void initOceanCube() {
        for (int i = 0; i < OCEANSIZEX; ++i) {
            for (int j = 0; j < OCEANSIZEY; ++j) {
                ocean[i][j][0] = ' ';
                ocean[i][j][1] = ' ';
                ocean[i][j][2] = ' ';
            }
        }
}

/**
 * \brief Populate our cube with fish placed at random positions within the first layer,
 * and set the corresponding second layer to the breed time of the fish.
 */
void fillOceanCubeWithFish() {
        for (int i = 0; i < numFish; ++i) {
            xPos = (int) random() % 10;
            yPos = (int) random() % 10;
            ocean[xPos][yPos][0] = 'f';
            ocean[xPos][yPos][1] = '0' + fishBreedTime;
        }
}

/**
 * \brief Populate our cube with sharks placed at random positions within the first layer,
 * and set the corresponding second and third layer to the breed time of the shark, and the starve time of the shark respectively.
 */
void fillOceanCubeWithShark() {
        for (int i = 0; i < numShark; ++i) {
            xPos = std::rand() % 10;
            yPos = std::rand() % 10;
            ocean[xPos][yPos][0] = 'S';
            ocean[xPos][yPos][1] = '0' + sharkBreedTime;
            ocean[xPos][yPos][2] = '0' + sharkStarveTime;
        }
}

/**
 * \brief Initializes ocean with ' ' characters, subsequently populating the ocean with fish and sharks, and storing the breed/starve time.
 */
void fillOcean() {
    initOceanCube();
    fillOceanCubeWithFish();
    fillOceanCubeWithShark();
}

/**
 * \brief Displays the first layer of the ocean, showing the positions of the fish and sharks.
 */
void displayOcean() {
    for (int i = 0; i < OCEANSIZEX; ++i) {
        for (int j = 0; j < OCEANSIZEY; ++j) {
            std::cout << ocean[i][j][0];
        }
        std::cout << std::endl;
    }
}

/**
 * \brief Helper methods to aid in visualisation of breed times
 */
void displayBreedTimes() {
    for (int i = 0; i < OCEANSIZEX; ++i) {
        for (int j = 0; j < OCEANSIZEY; ++j) {
            std::cout << ocean[i][j][1];
        }
        std::cout << std::endl;
    }
}

/**
 * \brief Helper methods to aid in visualisation of shark starve times
 */
void displayStarveTimes() {
    for (int i = 0; i < OCEANSIZEX; ++i) {
        for (int j = 0; j < OCEANSIZEY; ++j) {
            std::cout << ocean[i][j][2];
        }
        std::cout << std::endl;
    }
}

int main() {
    fillOcean();
    displayOcean();
    std::cout << std::endl;
    displayBreedTimes();
    std::cout << std::endl;
    displayStarveTimes();

    return 0;
}
