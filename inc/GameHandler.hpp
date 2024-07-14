#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <memory>
#include <string>
#include <vector>
#include "GameMode.hpp"

class GameHandler {
public:
    GameHandler();
    ~GameHandler();

    void initializeGame(const std::string& playerName, int numImages, int sequence, int gameMode);
    void startGame();
    void endGame();
    void displayNextImage();
    void giveFeedback();

private:
    std::string m_playerName;
    int m_numImagesToDisplay;
    int m_sequence;
    int m_gameMode;
    bool m_imageClicked;
    std::unique_ptr<GameMode> m_currentGameMode;
    std::vector<double> m_reactionTimes;
};

#endif // GAMEHANDLER_HPP
