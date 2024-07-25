#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

#include "GameMode.hpp"
#include "Gui.hpp"
#include "Config.hpp"


GameMode::GameMode() {}
GameMode::~GameMode() {}

GameMode::GameMode(std::string imageFolderPath)
  : m_imageFolderPath(imageFolderPath), m_currentSequence(0), m_currentIndex(0), m_imageClicked(0), m_lastClickInBoundingBox(0) {
}

BoundingBox GameMode::box(int x1, int y1, int x2, int y2) {
  return BoundingBox(x1, y1, x2, y2);
}

std::string GameMode::formatSequence(int sequence) {
  std::string sequenceString = std::to_string(sequence);
  sequenceString.insert(sequenceString.begin(), 4 - sequenceString.length(), '0');
  return sequenceString;
}

void GameMode::setBoxFolderPath(int sequence) {
  std::string sequenceString = formatSequence(sequence);
  m_boxFolder = bboxFolderPath + "/" + sequenceString + ".txt";
}


void GameMode::loadBoundingBoxes(int sequence, int numberOfImages) {
  setBoxFolderPath(sequence);

  std::ifstream infile(m_boxFolder);
  if (!infile.is_open()) {
    std::cout << "Error: Cannot open bounding box file" << std::endl;
  }

  m_Boxes.clear();
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    int frameIndex;
    iss >> frameIndex;

    // Only load required images
    if (frameIndex >= numberOfImages) {
      break;
    }

    iss.clear();
    iss.seekg(0, std::ios::beg);

    int objIndex, truncation, occlusion;
    std::string type;
    float alpha, x1, y1, x2, y2, h, w, l, t1, t2, t3, rotY;
    if (!(iss >> frameIndex >> objIndex >> type >> truncation >> occlusion >> alpha >> x1 >> y1 >> x2 >> y2 >> h >> w >> l >> t1 >> t2 >> t3 >> rotY)) {
      continue;
    }

    if (type == "DontCare") {
      continue;
    }
    BoundingBox box = this->box(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
    if (m_Boxes.size() <= frameIndex) {
      m_Boxes.resize(frameIndex + 1);
    }
    m_Boxes[frameIndex].push_back(cv::Rect(cv::Point(box.getX1(), box.getY1()), cv::Point(box.getX2(), box.getY2())));
  }
}

void GameMode::setImagePath(int image) {
  std::ostringstream imagePathStream;
  imagePathStream << m_imageFolderPath << "/" << std::setw(6) << std::setfill('0') << image << ".png";
  m_imagePath = imagePathStream.str();
}

bool GameMode::checkImage() {
  if (m_currentImage.empty()) {
    std::cout << "Error: Image not found: " << m_imagePath << std::endl;
    return 0;
  }
  return 1;
}

void GameMode::loadImage(int sequence, int image) {
  setImagePath(image);
  m_currentImage = cv::imread(m_imagePath);
  if (checkImage() == false) {
    return; // TODO: Do something else
  }
}

void GameMode::showBoundingBoxesForFrame(int frameIndex) {
  m_currentBoundingBoxes.clear();
  for (auto box : m_Boxes[frameIndex]) {
    m_currentBoundingBoxes.push_back(box);
}
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
}

bool GameMode::getImageClicked() {
  return m_imageClicked;
}

void GameMode::setImageClicked(bool imageClicked) {
  m_imageClicked = imageClicked;
}
