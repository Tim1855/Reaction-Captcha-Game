#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu myMenu;

    // display menu and get player information
    // myMenu.displayMenu();
    myMenu.promptGameMode();
    myMenu.setGameMode();


    if (myMenu.getGameStart()) {

        // initialize components
        // GameHandler gameHandler(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());
        GameHandler gameHandler("Tim", 5, 0, myMenu.getGameMode());

        // start game
        gameHandler.startGame();
    }

    return 0;
}

