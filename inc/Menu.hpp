#ifndef MENU_HPP
#define MENU_HPP

#include <iostream> // Inkludieren der Standardbibliothek für Ein-/Ausgabeoperationen

class Menu {
public:
    Menu(); // Konstruktor
    ~Menu(); // Destruktor

    // Methoden zur Anzeige und Abfrage der Benutzereingaben
    void displayMenu(); // Zeigt das Hauptmenü

    // Abfragen zur Eingabe von Spielerdaten und Spieloptionen
    void promptPlayerName(); // Fragt nach dem Namen des Spielers
    void promptNumberOfImages(); // Fragt nach der Anzahl der zu spielenden Bilder
    void promptSequence(); // Fragt nach der Sequenznummer der Bilder
    void promptGameMode(); // Fragt nach dem gewünschten Spielmodus
    void promptGameStart(); // Fragt, ob das Spiel gestartet werden soll

    // Setter-Methoden zur Aktualisierung der internen Zustände basierend auf Benutzereingaben
    void setPlayerName(); // Setzt den Namen des Spielers
    void setNumberOfImages(); // Setzt die Anzahl der Bilder
    void setSequence(); // Setzt die Sequenznummer
    void setGameMode(); // Setzt den Spielmodus
    void setGameStart(); // Startet das Spiel

    // Überprüfungsmethoden für Eingaben
    bool checkEmpty(std::string m_playerName); // Überprüft, ob der eingegebene String leer ist
    bool checkInteger(int integer); // Überprüft, ob der Wert eine gültige Ganzzahl ist
    bool checkBool(bool boolean); // Überprüft, ob der Wert ein gültiger boolescher Wert ist

    // Spezifische Überprüfungsmethoden für Spieloptionen
    bool checkNumberOfImages(int m_numberOfImages); // Überprüft die Gültigkeit der Anzahl der Bilder
    bool checkSequence(int m_sequence); // Überprüft die Gültigkeit der Sequenznummer
    bool checkGameMode(int m_gameMode); // Überprüft die Gültigkeit des Spielmodus
    bool checkGameStart(int m_gameStart); // Überprüft, ob das Spiel gestartet werden kann

    // Getter-Methoden
    std::string getPlayerName() const; // Gibt den Namen des Spielers zurück
    int getNumberOfImages() const; // Gibt die Anzahl der Bilder zurück
    int getSequence() const; // Gibt die Sequenznummer zurück
    int getGameMode() const; // Gibt den Spielmodus zurück
    int getGameStart() const; // Gibt den Startstatus des Spiels zurück

private:
    // Private Mitgliedsvariablen zur Speicherung von Benutzerdaten und Spieloptionen
    std::string m_playerName;
    int m_numberOfImages;
    int m_sequence;
    int m_gameMode;
    int m_gameStart;
};

#endif 
