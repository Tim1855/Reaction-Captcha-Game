#include "GameMode1.hpp"
#include "Gui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

GameMode1::GameMode1(const std::string& imageFolderPath, const std::string& bboxFolderPath)
    : m_imageFolderPath(imageFolderPath), m_bboxFolderPath(bboxFolderPath), m_currentSequence(0), m_currentIndex(0), m_imageClicked(nullptr) {
}

GameMode1::~GameMode1() {
}

bool GameMode1::loadBoundingBoxes(int sequence) {
    m_currentSequence = sequence;

    std::ostringstream bboxFilePathStream;
    bboxFilePathStream << m_bboxFolderPath << "/" << std::setw(4) << std::setfill('0') << sequence << ".txt";
    std::string bboxFilePath = bboxFilePathStream.str();

    std::ifstream infile(bboxFilePath);
    if (!infile.is_open()) {
        return false;
    }

    m_boundingBoxes.clear();
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int frameIndex, objIndex, truncation, occlusion;
        std::string type;
        float alpha, x1, y1, x2, y2, h, w, l, t1, t2, t3, rotY;
        if (!(iss >> frameIndex >> objIndex >> type >> truncation >> occlusion >> alpha >> x1 >> y1 >> x2 >> y2 >> h >> w >> l >> t1 >> t2 >> t3 >> rotY)) {
            continue;
        }

        if (type == "DontCare") {
            continue;
        }

        BoundingBox bbox(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
        if (m_boundingBoxes.size() <= frameIndex) {
            m_boundingBoxes.resize(frameIndex + 1);
        }
        m_boundingBoxes[frameIndex].push_back(cv::Rect(cv::Point(bbox.getX1(), bbox.getY1()), cv::Point(bbox.getX2(), bbox.getY2())));
    }

    return true;
}

void GameMode1::loadImageAndBoundingBox(int sequence, int index) {
    if (sequence != m_currentSequence) {
        if (!loadBoundingBoxes(sequence)) {
            return;
        }
    }
    
    m_currentIndex = index;

    std::ostringstream imagePathStream;
    imagePathStream << m_imageFolderPath << "/" << std::setw(6) << std::setfill('0') << index << ".png";
    std::string imagePath = imagePathStream.str();

    m_currentImage = cv::imread(imagePath);
    if (m_currentImage.empty()) {
        return;
    }

    if (!filterBoundingBoxesForFrame(index)) {
        return;
    }

    display();
}

bool GameMode1::filterBoundingBoxesForFrame(int frameIndex) {
    if (frameIndex < 0 || frameIndex >= static_cast<int>(m_boundingBoxes.size())) {
        return false;
    }

    m_currentBoundingBoxes.clear();
    for (const auto& bbox : m_boundingBoxes[frameIndex]) {
        m_currentBoundingBoxes.push_back(bbox);
    }

    if (!m_currentBoundingBoxes.empty()) {
        // Zufällige Auswahl einer Bounding Box
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, m_currentBoundingBoxes.size() - 1);
        int randomIndex = dis(gen);

        // Nur die zufällig ausgewählte Bounding Box behalten
        m_currentBoundingBoxes = { m_currentBoundingBoxes[randomIndex] };
    }

    return !m_currentBoundingBoxes.empty();
}

void GameMode1::startMode(int sequence, int numImages) {
    // Game mode started
}

void GameMode1::display() {
    if (m_currentImage.empty()) return;

    cv::Mat displayImage = m_currentImage.clone();
    for (const auto& bbox : m_currentBoundingBoxes) {
        cv::rectangle(displayImage, bbox, cv::Scalar(0, 0, 255), 2);
    }

    cv::imshow("Game Window", displayImage);
    cv::setMouseCallback("Game Window", [](int event, int x, int y, int flags, void* userdata) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            *static_cast<bool*>(userdata) = true;
        }
    }, static_cast<void*>(m_imageClicked));
}

void GameMode1::setMouseCallback(bool* imageClicked) {
    m_imageClicked = imageClicked;
}
