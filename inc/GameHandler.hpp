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

    void setImageFolderPath();
    void startGame();
    void endGame();
    void giveFeedback();

    std::string formatSequence(int sequence);
    std::string getImageFolderPath();

protected:
    std::string m_playerName;
    std::string m_imageFolderPath;
    int m_numberofImages;
    int m_sequence;
    int m_gameMode;
    int m_duration;
    std::vector<double> m_reactionTimes;
};

#endif // GAMEHANDLER_HPP
