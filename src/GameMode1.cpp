#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "GameMode1.hpp"

GameMode1::GameMode1(const std::string& imageFolderPath, const std::string& bboxFolderPath)
    : imageFolderPath(imageFolderPath), bboxFolderPath(bboxFolderPath), currentSequence(0), currentIndex(0) {
}

GameMode1::~GameMode1() {
}

bool GameMode1::loadBoundingBoxes(int sequence) {
    std::ostringstream bboxFilePathStream;
    bboxFilePathStream << bboxFolderPath << "/" << std::setw(4) << std::setfill('0') << sequence << ".txt";
    std::string bboxFilePath = bboxFilePathStream.str();

    std::ifstream infile(bboxFilePath);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open bounding box file: " << bboxFilePath << std::endl;
        return false;
    }

    boundingBoxes.clear();
    std::string line;
    int prevFrameIndex = -1;
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

        cv::Rect bbox(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2 - x1), static_cast<int>(y2 - y1));
        if (frameIndex != prevFrameIndex) {
            boundingBoxes.emplace_back();
            prevFrameIndex = frameIndex;
        }
        boundingBoxes.back().push_back(bbox);
    }

    std::cout << "Loaded " << boundingBoxes.size() << " frames of bounding boxes for sequence " << std::setw(4) << std::setfill('0') << sequence << std::endl;
    return true;
}

void GameMode1::loadImageAndBoundingBox(int sequence, int index) {
    std::ostringstream imagePathStream;
    imagePathStream << imageFolderPath << "/" << std::setw(6) << std::setfill('0') << index << ".png";
    std::string imagePath = imagePathStream.str();

    currentImage = cv::imread(imagePath);
    if (currentImage.empty()) {
        std::cerr << "Error: Image not found: " << imagePath << std::endl;
        return;
    }

    if (index < 0 || index >= boundingBoxes.size()) {
        std::cerr << "Error: Invalid index for bounding box" << std::endl;
        return;
    }

    if (!boundingBoxes[index].empty()) {
        boundingBox = boundingBoxes[index][0];
        std::cout << "Loaded bounding box: " << boundingBox << std::endl;
    } else {
        std::cerr << "No bounding boxes for frame " << index << std::endl;
    }

    display();
}

void GameMode1::startMode() {
    std::cout << "GameMode1 started" << std::endl;
    if (loadBoundingBoxes(currentSequence)) {
        loadImageAndBoundingBox(currentSequence, currentIndex);
    }
}

void GameMode1::processInput(int x, int y) {
    if (x == -1 && y == -1) {
        std::cout << "No valid input received." << std::endl;
        return;
    }

    std::cout << "Processing input in GameMode1 at (" << x << ", " << y << ")" << std::endl;
    if (boundingBox.contains(cv::Point(x, y))) {
        std::cout << "Hit! Bounding box clicked." << std::endl;
        currentIndex++;
        if (currentIndex >= boundingBoxes.size()) {
            currentSequence++;
            currentIndex = 0;
            if (!loadBoundingBoxes(currentSequence)) {
                std::cout << "No more sequences to load." << std::endl;
                return;
            }
        }
        loadImageAndBoundingBox(currentSequence, currentIndex);
    } else {
        std::cout << "Miss! Outside bounding box." << std::endl;
    }
}

void GameMode1::display() {
    std::cout << "Displaying GameMode1" << std::endl;
    if (currentImage.empty()) return;

    cv::Mat displayImage = currentImage.clone();
    cv::rectangle(displayImage, boundingBox, cv::Scalar(0, 0, 255), 2);

    cv::imshow("Game Window", displayImage);
    cv::waitKey(1);
}
