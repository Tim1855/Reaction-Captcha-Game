#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu menu;

    // display menu and get player information
    menu.displayMenu();

    // std::string playerName = menu.getPlayerName();
    // int numImages = menu.getNumberOfImages();
    int sequence = menu.getSequence();
    // int gameMode = menu.getGameMode();
    // bool gameStart = menu.getGameStart();
    std::string playerName = "Tim";
    int numImages = 30;
    // int sequence = 0;
    int gameMode = 2;
    bool gameStart = true;


    if (gameStart) {
    // initialize components
    GameHandler gameHandler;
    gameHandler.initializeGame(playerName, numImages, sequence, gameMode);
    // start game
    gameHandler.startGame();
    }

    return 0;
}

