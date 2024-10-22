#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <thread>

#include "GameMode2.hpp"
#include "BoundingBox.hpp"

GameMode2::GameMode2() : GameMode() {}

// Destruktor für GameMode2.
GameMode2::~GameMode2() {
}


// Zeigt das Bild und alle zugehörigen Bounding Boxes.
void GameMode2::display() {
    displayImage = Image.clone();
    for (auto box : m_Boxes) {
        cv::rectangle(displayImage, box, cv::Scalar(255, 0, 0), 2);
    }
    cv::imshow("Game Window", displayImage);
    cv::waitKey(1); // warte kurz um das Bild zu rendern
}

void GameMode2::updateTargetBox() {
    std::this_thread::sleep_for(std::chrono::duration<double>(chooseRandomDelay()));
    chooseRandomBox();
    cv::rectangle(displayImage, targetBox, cv::Scalar(0, 0, 255), 2);
    cv::imshow("Game Window", displayImage);
    cv::waitKey(1);
}


void GameMode2::setSpaceBarPress(bool spaceBarPress) {
    this->spaceBarPress = spaceBarPress;
}

bool GameMode2::getSpaceBarPress() {
    return this->spaceBarPress;
}
