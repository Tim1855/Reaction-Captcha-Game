#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    // initialize menu
    Menu myMenu;

    // display menu and get player information
    // myMenu.displayMenu();

    if (myMenu.getGameStart() || 1) {

        // initialize components
        // GameHandler gameHandler(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());
        GameHandler gameHandler("Tim", 5, 1, 2);
        // initialize game
        gameHandler.initializeGame();
        // start game
        gameHandler.startGame();
    }

    return 0;
}
