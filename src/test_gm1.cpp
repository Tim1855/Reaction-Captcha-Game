#include <iostream>
#include "Menu.hpp"
#include "GameHandler.hpp"

int main() {
    Menu menu;
    menu.displayMenu();

    std::string playerName = menu.getPlayerName();
    int numImages = menu.getNumberOfImages();
    int sequence = menu.getSequence();
    int gameMode = menu.getGameMode();

    GameHandler gameHandler;
    gameHandler.initializeGame(playerName, numImages, sequence, gameMode);
    gameHandler.startGame();

    return 0;
}
