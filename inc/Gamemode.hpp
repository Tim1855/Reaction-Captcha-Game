#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <string>

class GameMode {
public:
    virtual ~GameMode() = default;

    virtual void startMode(int sequence, int numImages) = 0;
    virtual void loadImageAndBoundingBox(int sequence, int index) = 0;
    virtual void display() = 0;
    virtual void setMouseCallback(bool* imageClicked) = 0;
};

#endif // GAMEMODE_HPP
