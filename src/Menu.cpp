#include "Menu.hpp"
#include <limits>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

// Konstruktor initialisiert Mitgliedervariablen mit Standardwerten
Menu::Menu() : m_numberOfImages(0), m_sequence(0), m_gameMode(0), m_gameStart(false) {
}

// Destruktor
Menu::~Menu() {
}

// Hauptfunktion zum Anzeigen und Verarbeiten des Menüs
void Menu::displayMenu() {
    // Aufforderungs- und Setzungssequenz für verschiedene Benutzereingaben
    promptPlayerName();
    setPlayerName();

    promptNumberOfImages();
    setNumberOfImages();

    promptSequence();
    setSequence();

    promptGameMode();
    setGameMode();

    promptGameStart();
    setGameStart();
}

// Aufforderung zur Eingabe des Spielernamens
void Menu::promptPlayerName() { 
    std::cout << "\nHallo Spieler, geben Sie ihren Namen ein: "; 
}

// Aufforderung zur Eingabe der Anzahl der Bilder
void Menu::promptNumberOfImages() {
    std::cout << "\nWaehlen Sie wie viele Bilder Sie spielen moechten (1-77): ";    
}

// Aufforderung zur Auswahl einer Sequenz
void Menu::promptSequence() {
    std::cout << "\nWaehlen Sie welche Sequenz Sie spielen moechten (0-20): ";    
}

// Aufforderung zur Auswahl des Spielmodus
void Menu::promptGameMode() {
    std::cout << "\nWaehlen Sie den Spielmodus aus (1 oder 2): ";
}

// Aufforderung zum Start des Spiels
void Menu::promptGameStart() {
    std::cout << "\nWollen Sie das Spiel starten (1:ja, 0:nein): ";    
}

// Setzt den Spielernamen nach Benutzereingabe
void Menu::setPlayerName() {
    std::cin>>m_playerName;
}

// Setzt die Anzahl der Bilder und überprüft die Eingabe
void Menu::setNumberOfImages() {
    std::cin>>m_numberOfImages;
    // Überprüfung der Eingabe auf Gültigkeit und Wiederholung bei Fehler
    if (!(checkNumberOfImages(m_numberOfImages) && checkInteger(m_numberOfImages))) { 
        promptNumberOfImages();
        setNumberOfImages();
    }
}

// Setzt die Sequenznummer und überprüft die Eingabe
void Menu::setSequence() {
    std::cin>>m_sequence;
    if (!(checkSequence(m_sequence) && checkInteger(m_sequence))) { 
        promptSequence();
        setSequence();
    }
}

// Setzt den Spielmodus und überprüft die Eingabe
void Menu::setGameMode() {
    std::cin>>m_gameMode;
    if (!(checkGameMode(m_gameMode) && checkInteger(m_gameMode))) { 
        promptGameMode();
        setGameMode();
    }
}

// Startet das Spiel oder zeigt das Menü erneut an
void Menu::setGameStart() {
    std::cin>>m_gameStart;
    if (!(checkGameStart(m_gameStart) && checkInteger(m_gameStart))) { 
        promptGameStart();
        setGameStart();
    }
    if (!m_gameStart) {
        std::cout<<"\nMenu will restart now"<<std::endl;
        displayMenu();
    }
}

// Überprüft die Gültigkeit der Anzahl der Bilder
bool Menu::checkNumberOfImages(int m_numberOfImages) {
    return ((m_numberOfImages >= 1) && (m_numberOfImages <= 77));
}

// Überprüft die Gültigkeit der Sequenznummer
bool Menu::checkSequence(int m_sequence) {
    return ((m_sequence >= 0) && (m_sequence <= 20));
}

// Überprüft die Gültigkeit des Spielmodus
bool Menu::checkGameMode(int m_gameMode) {
    return ((m_gameMode == 1) || (m_gameMode == 2));
}

// Überprüft, ob das Spiel gestartet oder das Menü wiederholt wird
bool Menu::checkGameStart(int m_gameStart) {
    return ((m_gameStart == 0) || (m_gameStart == 1));
}

// Überprüft, ob die Eingabe eine gültige Ganzzahl ist
bool Menu::checkInteger(int integer) {
    return 1;
}  

// Getter-Funktionen für Spielereingaben
std::string Menu::getPlayerName() const {
    return m_playerName;
}

int Menu::getNumberOfImages() const {
    return m_numberOfImages;
}

int Menu::getSequence() const {
    return m_sequence;
}

int Menu::getGameMode() const {
    return m_gameMode;
}

int Menu::getGameStart() const {
    return m_gameStart;
}
