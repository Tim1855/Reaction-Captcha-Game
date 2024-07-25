#ifndef GAMEMODE2_HPP
#define GAMEMODE2_HPP

#include "GameMode.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class GameMode2 : public GameMode {
public:
    GameMode2(std::string imageFolderPath, std::string bboxFolderPath);
    ~GameMode2();

    void display() override;
    void updateRedBoundingBox();
    void handleMouseClick(int x, int y) override;
    void setSpaceBarPress(bool spaceBarPress);
    bool getSpaceBarPress();
    void checkSpaceBarPress();

private:
    cv::Rect m_redBoundingBox;
    bool m_redBoundingBoxSet = 0;
    bool m_spaceBarPress;
};

#endif // GAMEMODE2_HPP
