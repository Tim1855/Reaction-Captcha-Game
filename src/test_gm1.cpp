#include "MouseHandler.hpp"
#include "TimeHandler.hpp"
#include "GameHandler.hpp"
#include "Menu.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // initialize components
    MouseHandler mouseHandler;
    TimeHandler timeHandler;
    GameHandler gameHandler;
    Menu menu;

    // display menu and get player information
    menu.displayMenu();
    std::string playerName = menu.getPlayerName();
    int numImages = menu.getNumberOfImages();
    int sequence = menu.getSequence();
    int gameMode = menu.getGameMode();
    bool gameStart = menu.getGameStart();


    if (gameStart) {
    gameHandler.initializeGame(playerName, numImages, sequence, gameMode);
    // start game
    gameHandler.startGame();
    }

    return 0;
}
