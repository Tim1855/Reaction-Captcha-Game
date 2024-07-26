#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>

#include "GameMode.hpp"
#include "Gui.hpp"
#include "Config.hpp"


GameMode::GameMode() {}
GameMode::~GameMode() {}

BoundingBox GameMode::box(int x1, int y1, int x2, int y2) {
  return BoundingBox(x1, y1, x2, y2);
}

std::string GameMode::formatSequence(int sequence) {
  std::string sequenceString = std::to_string(sequence);
  sequenceString.insert(sequenceString.begin(), 4 - sequenceString.length(), '0');
  return sequenceString;
}

std::string GameMode::formatImage(int image) {
  std::string imageString = std::to_string(image);
  imageString.insert(imageString.begin(), 6 - imageString.length(), '0');
  return imageString;
}

void GameMode::setBoxFolderPath(int sequence) {
  std::string sequenceString = formatSequence(sequence);
  m_boxFolder = bboxFolderPath + sequenceString + ".txt";
}

void GameMode::setImagePath(int image, int sequence) {
  std::string sequenceString = formatSequence(sequence);
  std::string imageString = formatImage(image);
  m_imagePath = imageFolder + sequenceString + "/" + imageString + ".png";
}


void GameMode::loadBoundingBoxes(int sequence, int image) {
  setBoxFolderPath(sequence);
  m_Boxes.clear();

  std::ifstream infile(m_boxFolder);
  if (!infile.is_open()) {
    std::cout << "Error: Cannot open bounding box file" << std::endl;
  }

  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    int frameIndex;
    iss >> frameIndex;

    iss.clear();
    iss.seekg(0, std::ios::beg);

    int objIndex, truncation, occlusion;
    std::string type;
    float alpha, x1, y1, x2, y2, h, w, l, t1, t2, t3, rotY;
    if (!(iss >> frameIndex >> objIndex >> type >> truncation >> occlusion >> alpha >> x1 >> y1 >> x2 >> y2 >> h >> w >> l >> t1 >> t2 >> t3 >> rotY)) {
      continue;
    }

    if (frameIndex != image) {
      continue;
    }

    if (type == "DontCare") {
      continue;
    }
    BoundingBox box = this->box(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
    m_Boxes.push_back(cv::Rect(cv::Point(box.getX1(), box.getY1()), cv::Point(box.getX2(), box.getY2())));
  }
}


bool GameMode::checkImage() {
  if (Image.empty()) {
    std::cout << "Error: Image not found: " << m_imagePath << std::endl;
    return 0;
  }
  return 1;
}

void GameMode::loadImage(int sequence, int image) {
  setImagePath(image, sequence);
  Image = cv::imread(m_imagePath);
  if (checkImage() == false) {
    return; // TODO: Do something else
  }
}


void GameMode::chooseRandomBox() {
  std::random_device random;
  std::mt19937 generator(random());
  std::uniform_int_distribution<> distribution(0, m_Boxes.size() - 1);
  targetBox = m_Boxes[distribution(generator)];
}

double GameMode::chooseRandomDelay() {
  std::random_device random;
  std::mt19937 generator(random());
  std::uniform_real_distribution<> distribution(1.0, 2.0);
  return distribution(generator);
}

void GameMode::display() {
  cv::Mat displayImage = Image.clone();
  cv::imshow("Game Window", displayImage);
  cv::waitKey(1); // Wait to ensure the image is being rendered
  chooseRandomBox();
  std::this_thread::sleep_for(std::chrono::duration<double>(chooseRandomDelay()));
  cv::rectangle(displayImage, targetBox, cv::Scalar(0, 0, 255), 2);
  cv::imshow("Game Window", displayImage);
  cv::waitKey(1);
}

void GameMode::setupCallback() {
  cv::setMouseCallback("Game Window", [](int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
      GameMode* handler = static_cast<GameMode*>(userdata);
      handler->checkClick(x, y);
    }
    }, this);
}

void GameMode::checkClick(int x, int y) {
  if (targetBox.contains(cv::Point(x, y))) {
    clickStatus = CORRECT_CLICK;
  }
  else {
    clickStatus = INCORRECT_CLICK;
  }
}

void GameMode::setClickStatus(ClickStatus clickStatus) {
  this->clickStatus = clickStatus;
}

ClickStatus GameMode::getClickStatus() {
  return this->clickStatus;
}


