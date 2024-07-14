#ifndef GAMEMODE2_HPP
#define GAMEMODE2_HPP

#include "GameMode.hpp"

class GameMode2 : public GameMode {
public:
    GameMode2();
    ~GameMode2();

    void startMode() override;
    void processInput(int x, int y) override;
    void display() override;

private:
    // Private members for GameMode2
};

#endif // GAMEMODE2_HPP
