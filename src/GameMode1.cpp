#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "GameMode1.hpp"
#include "Gui.hpp"
#include "BoundingBox.hpp"


GameMode1::GameMode1(std::string imageFolderPath, std::string bboxFolderPath)
    : GameMode(imageFolderPath,bboxFolderPath) {}

GameMode1::~GameMode1() {
}




