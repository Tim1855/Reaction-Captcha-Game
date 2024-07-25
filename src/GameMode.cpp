#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

#include "GameMode.hpp"
#include "BoundingBox.hpp"
#include "Gui.hpp"


GameMode::GameMode() {}
GameMode::~GameMode() {}

GameMode::GameMode(std::string imageFolderPath, std::string bboxFolderPath)
  : m_imageFolderPath(imageFolderPath), m_bboxFolderPath(bboxFolderPath), m_currentSequence(0), m_currentIndex(0), m_imageClicked(0), m_lastClickInBoundingBox(0) {
}

bool GameMode::loadBoundingBoxes(int sequence) {
  std::ostringstream bboxFolderPathStream;
  bboxFolderPathStream << m_bboxFolderPath << "/" << std::setw(4) << std::setfill('0') << sequence << ".txt";
  std::string bboxFolderPath = bboxFolderPathStream.str();

  std::ifstream infile(bboxFolderPath);
  if (!infile.is_open()) {
    std::cout << "Error: Cannot open bounding box file" << std::endl;
    return 0;
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

  return 1;
}

void GameMode::loadImageAndBoundingBox(int sequence, int index) {
  loadBoundingBoxes(sequence);
  std::ostringstream imagePathStream;
  imagePathStream << m_imageFolderPath << "/" << std::setw(6) << std::setfill('0') << index << ".png";
  std::string imagePath = imagePathStream.str();
  std::cout << imagePath;
  m_currentImage = cv::imread(imagePath);
  if (m_currentImage.empty()) {
    std::cout << "Error: Image not found: " << std::endl;
    return;
  }
  filterBoundingBoxesForFrame(index);
  display();
}

void GameMode::filterBoundingBoxesForFrame(int frameIndex) {
  std::cout << "\nFrameIndex: " << frameIndex;
  std::cout << "\nBounding Box Size: " << m_boundingBoxes.size();
  if (frameIndex < 0 || frameIndex >= static_cast<int>(m_boundingBoxes.size())) {
    std::cout << "Error: Invalid frame index for bounding box" << std::endl;
    return;
  }
  m_currentBoundingBoxes.clear();
  for (auto bbox : m_boundingBoxes[frameIndex]) {
    m_currentBoundingBoxes.push_back(bbox);
  }
  return;
}

bool GameMode::lastClickInBoundingBox() {
  return m_lastClickInBoundingBox;
}

void GameMode::display() {
  cv::Mat displayImage = m_currentImage.clone();

  // Select a random bounding box
  std::random_device random;
  std::mt19937 generator(random());
  std::uniform_int_distribution<> distribution(0, m_currentBoundingBoxes.size() - 1);
  m_targetBoundingBox = m_currentBoundingBoxes[distribution(generator)];

  cv::rectangle(displayImage, m_targetBoundingBox, cv::Scalar(0, 0, 255), 2);
  cv::imshow("Game Window", displayImage);
  setupCallback();
}

void GameMode::setupCallback() {
  cv::setMouseCallback("Game Window", [](int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
      GameMode* handler = static_cast<GameMode*>(userdata);
      handler->handleMouseClick(x, y);
      handler->m_imageClicked = 1;
    }
    }, this);
}

void GameMode::handleMouseClick(int x, int y) {
  if (m_targetBoundingBox.contains(cv::Point(x, y))) {
    m_lastClickInBoundingBox = 1;
  }
  else {
    m_lastClickInBoundingBox = 0;
  }
  m_imageClicked = 1;
}

bool GameMode::getImageClicked() {
  return m_imageClicked;
}

void GameMode::setImageClicked(bool imageClicked) {
  m_imageClicked = imageClicked;
}
