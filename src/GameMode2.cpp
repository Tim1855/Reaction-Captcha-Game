#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

#include "GameMode2.hpp"
#include "BoundingBox.hpp"
#include "Gui.hpp"

GameMode2::GameMode2(std::string imageFolderPath, std::string bboxFolderPath) : GameMode(imageFolderPath, bboxFolderPath) {}

GameMode2::~GameMode2() {
}


void GameMode2::display() {
    if (m_currentImage.empty()) return;

    cv::Mat displayImage = m_currentImage.clone();
    for (const auto& bbox : m_currentBoundingBoxes) {
        cv::Scalar color = (bbox == m_redBoundingBox) ? cv::Scalar(0, 0, 255) : cv::Scalar(255, 0, 0);
        cv::rectangle(displayImage, bbox, color, 2);
    }

    cv::imshow("Game Window", displayImage);
    updateRedBoundingBox();
    setupCallback();
}

void GameMode2::updateRedBoundingBox() {
    if (!m_redBoundingBoxSet) {
        int delay = 1000 + (std::rand() % 1000); // 1-2 seconds delay
        cv::waitKey(delay); // Wait for the delay
        if (!m_currentBoundingBoxes.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, m_currentBoundingBoxes.size() - 1);
            m_redBoundingBox = m_currentBoundingBoxes[dis(gen)];
            m_redBoundingBoxSet = 1;
            display();
            m_redBoundingBoxSet = 0;
        }
    }
}


void GameMode2::handleMouseClick(int x, int y) {
    if (m_redBoundingBox.contains(cv::Point(x, y))) {
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
