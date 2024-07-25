#ifndef GAMEMODE1_HPP
#define GAMEMODE1_HPP

#include "GameMode.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class GameMode1 : public GameMode {
public:
    GameMode1(std::string imageFolderPath);
    ~GameMode1();
};

#endif // GAMEMODE1_HPP
