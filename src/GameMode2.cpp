#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <thread>

#include "GameMode2.hpp"
#include "BoundingBox.hpp"
#include "Gui.hpp"

GameMode2::GameMode2() : GameMode() {}

GameMode2::~GameMode2() {
}


void GameMode2::display() {
    displayImage = Image.clone();
    for (auto box : m_Boxes) {
        cv::rectangle(displayImage, box, cv::Scalar(255, 0, 0), 2);
    }
    cv::imshow("Game Window", displayImage);
    cv::waitKey(1); // Wait to ensure the image is being rendered
}

void GameMode2::updateTargetBox() {
    std::this_thread::sleep_for(std::chrono::duration<double>(chooseRandomDelay()));
    chooseRandomBox();
    cv::rectangle(displayImage, targetBox, cv::Scalar(0, 0, 255), 2);
    cv::imshow("Game Window", displayImage);
    cv::waitKey(1); // Wait to ensure the image is being rendered
}


bool GameMode2::checkSpaceBarPress() {
    if (cv::waitKey(1) == 32) { // allow opencv to process keyboard and check for spacebar press (ASCII code 32)
        return 1;
    }
    return 0;
}
