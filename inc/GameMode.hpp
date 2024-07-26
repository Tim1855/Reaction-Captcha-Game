#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "BoundingBox.hpp"


class GameMode {
protected:
    std::string m_imageFolderPath;
    std::string m_imagePath;
    std::string m_boxFolder;
    bool m_imageClicked;
    bool m_lastClickInBoundingBox;
    cv::Mat Image;
    cv::Mat displayImage;
    std::vector<cv::Rect> m_Boxes;
    cv::Rect targetBox;
public:
    GameMode();
    virtual ~GameMode();

    virtual void loadBoundingBoxes(int sequence, int numberOfImages);
    virtual void loadImage(int sequence, int index);
    virtual bool checkImage();
    virtual void display();
    virtual void handleMouseClick(int x, int);
    virtual bool lastClickInBoundingBox();
    virtual void setupCallback();
    virtual bool getImageClicked();
    virtual void setImageClicked(bool imageClicked);
    virtual void setBoxFolderPath(int sequence);
    virtual std::string formatSequence(int sequence);
    virtual std::string formatImage(int image);
    virtual void setImagePath(int image, int sequence);
    BoundingBox box(int x1, int y1, int x2, int y2);
    virtual void chooseRandomBox();
    double chooseRandomDelay();
};

#endif // GAMEMODE_HPP
