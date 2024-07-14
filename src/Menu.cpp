#include "Menu.hpp"


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
    std::cin >> m_PlayerName;
    setPlayerName();
}

void Menu::promptNumberOfImages() {
    std::cout << "\nWaehlen Sie wie viele Bilder Sie spielen moechten (1-77): ";
    std::cin >> m_numberOfImages;
    setNumberOfImages();
}

void Menu::promptSequence() {
    std::cout << "\nWaehlen Sie welche Sequenz Sie spielen moechten (0-20): ";
    std::cin >> m_sequence;
    setSequence();
}

void Menu::promptGameMode() {
    std::cout << "\nWaehlen Sie den Spielmodus aus (1 oder 2): ";
    std::cin >> m_gameMode;
    setGameMode();
}

void Menu::promptGameStart() {
    std::cout << "\n\nWollen Sie das Spiel starten (1:ja, 0:nein): ";
    std::cin >> m_gameStart;
    setGameStart();
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


void Menu::setPlayerName() {
    if (!checkInputPlayerName(m_PlayerName))
    {
        promptPlayerName();
    }
}

void Menu::setNumberOfImages() {
    if (!checkInputNumberOfImages(m_numberOfImages))
    {
        promptNumberOfImages();
    }
}

void Menu::setSequence() {
    if (!checkInputSequence(m_sequence))
    {
        promptSequence();
    }
}

void Menu::setGameMode() {
    if (!checkInputGameMode(m_gameMode))
    {
        promptGameMode();
    }
}

void Menu::setGameStart() {
    if (!checkInputGameStart(m_gameStart))
    {
        promptGameStart();
    }
    if (!m_gameStart) {
        displayMenu();
    }
}


bool Menu::checkInputPlayerName(std::string m_PlayerName)
{
    return 1;
}

bool Menu::checkInputNumberOfImages(int m_numberOfImages)
{

    if ((m_numberOfImages >= 1) && (m_numberOfImages <= 77)) // smallest sequence has 77 images (0012)
    {
        return 1;
    }

    return 0;
}

bool Menu::checkInputSequence(int m_sequence) {
    if ((m_sequence >= 0) && (m_sequence <= 20))
    {
        return 1;
    }
    return 0;
}

bool Menu::checkInputGameMode(int m_gameMode) {
    if ((m_gameMode >= 1) && (m_gameMode <= 2)) {
        return 1;
    }
    return 0;
}

bool Menu::checkInputGameStart(int m_gameStart) {
    if ((m_gameMode >= 0) && (m_gameMode <= 1)) {
        return 1;
    }
    return 0;
}