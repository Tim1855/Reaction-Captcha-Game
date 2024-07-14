#ifndef GAMEMODE1_HPP
#define GAMEMODE1_HPP

#include "GameMode.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class GameMode1 : public GameMode {
public:
    GameMode1(const std::string& imageFolderPath, const std::string& bboxFolderPath);
    ~GameMode1();

    void startMode(int sequence, int numImages) override;
    void loadImageAndBoundingBox(int sequence, int index) override;
    void display() override;
    void setMouseCallback(bool* imageClicked) override;

private:
    bool loadBoundingBoxes(int sequence);
    bool filterBoundingBoxesForFrame(int frameIndex);

    std::string m_imageFolderPath;
    std::string m_bboxFolderPath;
    int m_currentSequence;
    int m_currentIndex;
    cv::Mat m_currentImage;
    bool* m_imageClicked;

    std::vector<std::vector<cv::Rect>> m_boundingBoxes;
    std::vector<cv::Rect> m_currentBoundingBoxes;
};

#endif // GAMEMODE1_HPP
