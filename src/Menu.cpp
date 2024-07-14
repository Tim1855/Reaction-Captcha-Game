#include "Menu.hpp"
#include <limits>
#include <iostream>

Menu::Menu(/* args */) : m_numberOfImages(0), m_sequence(0), m_gameMode(0), m_gameStart(false) {
}

Menu::~Menu() {
}

void Menu::displayMenu() {
    promptPlayerName();
    promptNumberOfImages();
    promptSequence();
    promptGameMode();
    promptGameStart();
}

void Menu::promptPlayerName() {
    std::cout << "Hallo Spieler, geben Sie ihren Namen ein: ";
    setPlayerName();
}

void Menu::promptNumberOfImages() {
    std::cout << "\nWaehlen Sie wie viele Bilder Sie spielen moechten: ";
    setNumberOfImages();
}

void Menu::promptSequence() {
    std::cout << "\nWaehlen Sie welche Sequenz Sie spielen moechten (0000-0020): ";
    setSequence();
}

void Menu::promptGameMode() {
    std::cout << "\nWaehlen Sie den Spielmodus (1 oder 2): ";
    setGameMode();
}

void Menu::promptGameStart() {
    std::cout << "\nWollen Sie das Spiel starten (ja:1, nein:0)?: ";
    setGameStart();
}

void Menu::setPlayerName() {
    std::cin >> m_PlayerName;
    // checkInputPlayerName();
}

void Menu::setNumberOfImages() {
    std::cin >> m_numberOfImages;
    while (!checkInputNumberOfImages()) {
        std::cin >> m_numberOfImages;
    }
}

void Menu::setSequence() {
    std::cin >> m_sequence;
    while (!checkInputSequence()) {
        std::cin >> m_sequence;
    }
}

void Menu::setGameMode() {
    std::cin >> m_gameMode;
    while (!checkInputGameMode()) {
        std::cin >> m_gameMode;
    }
}

void Menu::setGameStart() {
    std::cin >> m_gameStart;
    // checkInputGameStart();
}

bool Menu::checkInputPlayerName() {
    return true; // Implementieren Sie die Überprüfung für den Spielernamen, falls erforderlich
}

bool Menu::checkInputNumberOfImages() {
    if (std::cin.fail() || m_numberOfImages <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nGeben Sie eine gültige Anzahl von Bildern ein: ";
        return false;
    }
    return true;
}

bool Menu::checkInputSequence() {
    if (std::cin.fail() || m_sequence < 0 || m_sequence > 20) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nGeben Sie eine Zahl zwischen 0000 und 0020 ein: ";
        return false;
    }
    return true;
}

bool Menu::checkInputGameMode() {
    if (std::cin.fail() || (m_gameMode != 1 && m_gameMode != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nUngueltige Eingabe. Bitte waehlen Sie den Spielmodus (1 oder 2): ";
        return false;
    }
    return true;
}

bool Menu::checkInputGameStart() {
    return true; // Implementieren Sie die Überprüfung für den Spielstart, falls erforderlich
}

std::string Menu::getPlayerName() const {
    return m_PlayerName;
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

bool Menu::getGameStart() const {
    return m_gameStart;
}
