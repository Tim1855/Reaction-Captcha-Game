#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "BoundingBox.hpp"

enum ClickStatus {
    NO_CLICK,
    CORRECT_CLICK,
    INCORRECT_CLICK
};

class GameMode {
protected:
    std::string m_imageFolderPath;
    std::string m_imagePath;
    std::string m_boxFolder;
    cv::Mat Image;
    cv::Mat displayImage;
    std::vector<cv::Rect> m_Boxes;
    cv::Rect targetBox;
    ClickStatus clickStatus;
public:
    GameMode();
    virtual ~GameMode();

    void loadBoundingBoxes(int sequence, int numberOfImages);
    void loadImage(int sequence, int index);
    bool checkImage();
    void checkClick(int x, int y);
    void setupCallback();
    void setBoxFolderPath(int sequence);
    std::string formatSequence(int sequence);
    std::string formatImage(int image);
    void setImagePath(int image, int sequence);
    BoundingBox box(int x1, int y1, int x2, int y2);
    void chooseRandomBox();
    double chooseRandomDelay();
    ClickStatus getClickStatus();
    void setClickStatus(ClickStatus clickStatus);
    virtual void display();
    virtual void updateTargetBox() {};
    virtual bool checkSpaceBarPress();
};

#endif // GAMEMODE_HPP
