#include "Menu.hpp"
#include <limits> // Für std::numeric_limits

Menu::Menu() {
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
    std::cout << "\nWaehlen Sie den Spielmodus (1, 2): ";
    setGameMode();
}

void Menu::promptGameStart() {
    std::cout << "\nWollen Sie das Spiel starten (ja:1, nein:0)?: ";
    setGameStart();
}

void Menu::setPlayerName() {
    std::cin >> m_PlayerName;
}

void Menu::setNumberOfImages() {
    std::cin >> m_numberOfImages;
}

void Menu::setSequence() {
    std::cin >> m_sequence;
    while (!checkInputSequence()) {
        std::cin >> m_sequence;
    }
}

void Menu::setGameMode() {
    std::cin >> m_gameMode;
}

void Menu::setGameStart() {
    std::cin >> m_gameStart;
}

bool Menu::checkInputSequence() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nGebe einen Integer ein: ";
        return false;
    } else if (m_sequence < 0 || m_sequence > 20) {
        std::cout << "\nGebe eine Zahl zwischen 0 - 20 ein: ";
        return false;
    } else {
        return true;
    }
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
