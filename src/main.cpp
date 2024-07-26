#include "Menu.hpp"
#include "GameHandler.cpp"

int main() {
    Menu myMenu;

    myMenu.displayMenu();

    if (myMenu.getGameStart()) {
        // initialize components
        GameHandler gameHandler(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());
        // start game
        gameHandler.startGame();
    }

    return 0;
}
