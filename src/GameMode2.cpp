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

GameMode2::GameMode2(std::string imageFolderPath) : GameMode(imageFolderPath) {}

GameMode2::~GameMode2() {
}


void GameMode2::display() {

    cv::Mat displayImage = m_currentImage.clone();
    for (const auto& box : m_currentBoundingBoxes) {
        cv::Scalar color = (box == targetBox) ? cv::Scalar(0, 0, 255) : cv::Scalar(255, 0, 0);
        cv::rectangle(displayImage, box, color, 2);
    }

    cv::imshow("Game Window", displayImage);
    cv::waitKey(1); // Wait to ensure the image is being rendered
    updateRedBoundingBox();
}

void GameMode2::updateRedBoundingBox() {
    if (!m_redBoundingBoxSet) {
        std::this_thread::sleep_for(std::chrono::duration<double>(chooseRandomDelay()));
        chooseRandomBox();
        m_redBoundingBoxSet = 1;
        display();
        m_redBoundingBoxSet = 0;
    }
}


void GameMode2::handleMouseClick(int x, int y) {
    if (targetBox.contains(cv::Point(x, y))) {
        m_lastClickInBoundingBox = 1;
    }
    else {
        m_lastClickInBoundingBox = 0;
    }
    m_imageClicked = 1;
}

void GameMode2::setSpaceBarPress(bool spaceBarPress) {
    m_spaceBarPress = spaceBarPress;
}

bool GameMode2::getSpaceBarPress() {
    return m_spaceBarPress;
}

void GameMode2::checkSpaceBarPress() {
    if (cv::waitKey(30) == 32) { // wait briefly and check for spacebar press (ASCII code 32)
        m_spaceBarPress = 1;
    }
}
