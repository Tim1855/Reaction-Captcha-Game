#ifndef GAMEMODE2_HPP
#define GAMEMODE2_HPP

#include "GameMode.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class GameMode2 : public GameMode {
public:
    GameMode2();
    ~GameMode2();

    void display() override;
    void updateTargetBox() override;
    bool getSpaceBarPress() override;
    void setSpaceBarPress(bool spaceBarPress) override;
    private:
    bool spaceBarPress;
};

#endif // GAMEMODE2_HPP
