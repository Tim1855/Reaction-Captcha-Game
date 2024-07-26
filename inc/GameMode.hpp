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

    virtual void loadBoundingBoxes(int sequence, int numberOfImages);
    virtual void loadImage(int sequence, int index);
    virtual bool checkImage();
    virtual void display();
    virtual void checkClick(int x, int y);
    virtual void setupCallback();
    virtual void setBoxFolderPath(int sequence);
    virtual std::string formatSequence(int sequence);
    virtual std::string formatImage(int image);
    virtual void setImagePath(int image, int sequence);
    virtual BoundingBox box(int x1, int y1, int x2, int y2);
    virtual void chooseRandomBox();
    virtual double chooseRandomDelay();
    virtual ClickStatus getClickStatus();
    virtual void setClickStatus(ClickStatus clickStatus);
};

#endif // GAMEMODE_HPP
