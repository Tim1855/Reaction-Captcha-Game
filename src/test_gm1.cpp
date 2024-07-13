#include "MouseHandler.hpp"
#include "TimeHandler.hpp"
#include "GameHandler.hpp"
#include "Menu.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Initialisieren der Komponenten
    MouseHandler mouseHandler;
    TimeHandler timeHandler;
    GameHandler gameHandler;
    Menu menu;

    // Menü anzeigen und Benutzereingaben erfassen
    menu.displayMenu();
    std::string playerName = menu.getPlayerName();
    int numImages = menu.getNumberOfImages();
    int sequence = menu.getSequence();
    int gameMode = menu.getGameMode();

    // Spiel initialisieren
    gameHandler.initializeGame(playerName, numImages, sequence, gameMode);

    // Spiel starten
    gameHandler.startGame();

    return 0;
}
