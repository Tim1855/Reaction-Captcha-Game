#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "Menu.hpp"
#include "Gui.hpp"
#include "MouseHandler.hpp"
#include "TimeHandler.hpp"
#include "GameMode.hpp"
#include "GameMode1.hpp"
#include "GameMode2.hpp"
#include <memory>
#include <string>
#include <vector>
#include <tuple>

class GameHandler {
public:
    GameHandler();
    ~GameHandler();

    void initializeGame(const std::string& playerName, int numImages, int sequence, int gameMode);
    void startGame();
    void endGame();

private:
    Menu menu;
    Gui gui;
    MouseHandler mouseHandler;
    TimeHandler timeHandler;
    std::unique_ptr<GameMode> currentGameMode;
    int numImagesToDisplay;
    std::string playerName;
    std::vector<std::tuple<int, double>> reactionTimes; // Bildnummer, Reaktionszeit

    void loadImages(int sequence);
    void handleUserInput();
    void displayNextImage();
    void processReaction(int imageIndex, double reactionTime);
    void giveFeedback();
};

#endif // GAMEHANDLER_HPP
