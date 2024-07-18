#include "Menu.hpp"           // Inkludiert die Definition der Menu-Klasse.
#include "GameHandler.cpp"    // Inkludiert die Implementierung des GameHandlers.

int main() {
    // Erstellt eine Instanz der Menu-Klasse.
    Menu myMenu;

    // Zeigt das Menü an und holt die Spielerinformationen.
    myMenu.displayMenu();

    // Überprüft, ob das Spiel gestartet werden soll, basierend auf der Benutzereingabe.
    if (myMenu.getGameStart()) {
        // Erstellt eine Instanz des GameHandlers.
        GameHandler gameHandler;

        // Initialisiert das Spiel mit den Spielerinformationen und den ausgewählten Einstellungen.
        gameHandler.initializeGame(myMenu.getPlayerName(), myMenu.getNumberOfImages(), myMenu.getSequence(), myMenu.getGameMode());

        // Startet das Spiel.
        gameHandler.startGame();
    }

    // Beendet das Programm und gibt 0 zurück.
    return 0;
}
