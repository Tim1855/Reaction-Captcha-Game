#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <memory>
#include <string>
#include <vector>

#include "GameMode.hpp"


class GameHandler {
public:
    GameHandler();
    GameHandler(std::string playerName, int numberofImages, int sequence, int gameMode);
    ~GameHandler();

    void startGame();
    void endGame();
    void giveFeedback();

protected:
    std::string m_playerName;
    int m_numberofImages;
    int m_sequence;
    int m_gameMode;
    std::vector<double> m_reactionTimes;
};

#endif // GAMEHANDLER_HPP
