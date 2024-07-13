#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

class GameMode {
public:
    virtual ~GameMode() = default;
    virtual void startMode() = 0;
    virtual void processInput(int x, int y) = 0;
    virtual void display() = 0;
};

#endif // GAMEMODE_HPP
