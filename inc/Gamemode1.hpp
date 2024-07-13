#ifndef GAMEMODE1_HPP
#define GAMEMODE1_HPP

#include "GameMode.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class GameMode1 : public GameMode {
public:
    GameMode1(const std::string& imageFolderPath, const std::string& bboxFolderPath);
    ~GameMode1();

    void startMode() override;
    void processInput(int x, int y) override;
    void display() override;

    void loadImageAndBoundingBox(int sequence, int index);

    int getCurrentSequence() const { return currentSequence; }

private:
    cv::Mat currentImage;
    cv::Rect boundingBox;
    std::string imageFolderPath;
    std::string bboxFolderPath;
    std::vector<std::vector<cv::Rect>> boundingBoxes;
    int currentSequence;
    int currentIndex;

    bool loadBoundingBoxes(int sequence);
};

#endif // GAMEMODE1_HPP
