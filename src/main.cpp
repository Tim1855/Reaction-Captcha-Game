#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu myMenu;

    // display menu and get player information
    myMenu.displayMenu();

    if (myMenu.getGameStart()) {
    // initialize components
    GameHandler gameHandler;
    gameHandler.initializeGame(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());
    // start game
    gameHandler.startGame();
    }

    return 0;
}

