#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu myMenu;

    // display menu and get player information
    myMenu.displayMenu();

    if (myMenu.getGameStart()) {

    // initialize components
    GameHandler gameHandler(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());

    // initialize game
    gameHandler.initializeGame();
    // start game
    gameHandler.startGame();
    }

    return 0;
}

