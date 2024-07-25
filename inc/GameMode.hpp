#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


class GameMode {
protected:
    std::string m_imageFolderPath;
    std::string m_bboxFolderPath;
    int m_currentSequence;
    int m_currentIndex;
    int m_gameMode;
    bool m_imageClicked;
    bool m_lastClickInBoundingBox;
    cv::Mat m_currentImage;
    std::vector<std::vector<cv::Rect>> m_boundingBoxes;
    std::vector<cv::Rect> m_currentBoundingBoxes;
    cv::Rect m_targetBoundingBox;
public:
    GameMode();
    GameMode(std::string imageFolderPath, std::string bboxFolderPath);
    virtual ~GameMode();

    virtual bool loadBoundingBoxes(int sequence);
    virtual void loadImageAndBoundingBox(int sequence, int index);
    virtual void display();
    virtual void filterBoundingBoxesForFrame(int frameIndex);
    virtual void handleMouseClick(int x, int);
    virtual bool lastClickInBoundingBox();
    virtual void setupCallback();
    virtual bool getImageClicked();
    virtual void setImageClicked(bool imageClicked);
};

#endif // GAMEMODE_HPP
