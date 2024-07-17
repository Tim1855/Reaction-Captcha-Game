#include <limits>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

#include "Menu.hpp"
#include "Inputchecker.hpp"

Menu::Menu() : m_numberOfImages(0), m_sequence(0), m_gameMode(0), m_gameStart(false) {
}

Menu::~Menu() {
}

void Menu::displayMenu() {
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

//Promptfunktionen für die Spielereingaben
void Menu::promptPlayerName() {
    std::cout << "\nHallo Spieler, geben Sie ihren Namen ein: ";
}

void Menu::promptNumberOfImages() {
    std::cout << "\nWaehlen Sie wie viele Bilder Sie spielen moechten (1-77): ";
}

void Menu::promptSequence() {
    std::cout << "\nWaehlen Sie welche Sequenz Sie spielen moechten (0-20): ";
}

void Menu::promptGameMode() {
    std::cout << "\nWaehlen Sie den Spielmodus aus (1 oder 2): ";
}

void Menu::promptGameStart() {
    std::cout << "\nWollen Sie das Spiel starten (1:ja, 0:nein): ";
}

//Setter Funktionen für die Spielereingaben
void Menu::setPlayerName() {
    std::getline(std::cin, m_input);
    if (checkDataType<std::string>(m_input)) {
        m_playerName = m_input;
    }
    else {
        promptPlayerName();
        setPlayerName();
    }
}

void Menu::setNumberOfImages() {
    std::getline(std::cin, m_input);
    if (checkDataType<int>(m_input)) {
        m_numberOfImages = std::stoi(m_input);
        if ((m_numberOfImages < 1) && (m_numberOfImages > 77)) {
            promptNumberOfImages();
            setNumberOfImages();
        }
    }
    else {
        promptNumberOfImages();
        setNumberOfImages();
    }
}

void Menu::setSequence() {
    std::getline(std::cin, m_input);
    if (checkDataType<int>(m_input)) {
        m_sequence = std::stoi(m_input);
        if ((m_sequence < 1) || (m_sequence > 20)) {
            promptSequence();
            setSequence();
        }
    }
    else {
        promptSequence();
        setSequence();
    }
}

void Menu::setGameMode() {
    std::getline(std::cin, m_input);
    if (checkDataType<int>(m_input)) {
        m_gameMode = std::stoi(m_input);
        if ((m_gameMode != 1) && (m_gameMode != 2)) {
            promptGameMode();
            setGameMode();
        }
    }
    else {
        promptGameMode();
        setGameMode();
    }
}

void Menu::setGameStart() {
    std::getline(std::cin, m_input);
    if (checkDataType<int>(m_input)) {
        m_gameStart = std::stoi(m_input);
        if (m_gameStart == 0) {
            displayMenu();
        }
        else if (m_gameStart == 1) {
            std::cout << "\nSpielbeginn: ";
        }
        else {
            promptGameStart();
            setGameStart();
        }
    }
    else {
        promptGameStart();
        setGameStart();
    }
}

//Checker Funktionen testen Inputrange
bool Menu::checkNumberOfImages(int m_numberOfImages) {
    return ((m_numberOfImages >= 1) && (m_numberOfImages <= 77)); // smallest sequence has 77 images (0012)
}

bool Menu::checkSequence(int m_sequence) {
    return ((m_sequence >= 0) && (m_sequence <= 20));
}

bool Menu::checkGameMode(int m_gameMode) {
    return ((m_gameMode == 1) || (m_gameMode == 2));
}

bool Menu::checkGameStart(int m_gameStart) {
    return ((m_gameStart == 0) || (m_gameStart == 1));
}


//Getter Funktionen für die Spielereingaben
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