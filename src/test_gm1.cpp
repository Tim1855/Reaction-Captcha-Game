#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu menu;

    // display menu and get player information
    menu.displayMenu();
    std::string playerName = menu.getPlayerName();
    int numImages = menu.getNumberOfImages();
    int sequence = menu.getSequence();
    int gameMode = menu.getGameMode();
    bool gameStart = menu.getGameStart();


    if (gameStart) {
    // initialize components
    
    gameHandler.initializeGame(playerName, numImages, sequence, gameMode);
    // start game
    gameHandler.startGame();
    }

    return 0;
}
