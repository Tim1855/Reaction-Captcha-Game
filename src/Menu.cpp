#include "Menu.hpp"
#include "InputChecker.cpp"


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
    std::cout << "\nWaehlen Sie wie viele Bilder Sie spielen moechten (1-77): ";
    setNumberOfImages();
}

void Menu::promptSequence() {
    std::cout << "\nWaehlen Sie welche Sequenz Sie spielen moechten (0-20): ";
    setSequence();
}

void Menu::promptGameMode() {
    std::cout << "\nWaehlen Sie den Spielmodus aus (1 oder 2): ";
    setGameMode();
}

void Menu::promptGameStart() {
    std::cout << "\n\nWollen Sie das Spiel starten (1:ja, 0:nein): ";
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
    while (!checkInputPlayerName(m_PlayerName)) { // loop until checkInput returns 1, which indicates that the input is right
        promptPlayerName;
    }
}

void Menu::setNumberOfImages() {
    while (!checkInputGameStart(m_numberOfImages)) {
        promptNumberOfImages;
    }
}

void Menu::setSequence() {
    while (!checkInputGameStart(m_sequence)) {
        promptSequence;
    }
}

void Menu::setGameMode() {
    while (!checkInputGameStart(m_gameMode)) {
        promptGameMode;
    }
}

void Menu::setGameStart() {
    while (!checkInputGameStart(m_gameStart)) {
        promptGameStart;
    }
}


bool Menu::checkInputPlayerName(std::string m_PlayerName)
{
    if (!checker.checkDatatype(m_PlayerName))
    {
        return 0;
    }
}

bool Menu::checkInputNumberOfImages(int m_numberOfImages)
{
    if (!checker.checkDatatype(m_numberOfImages))
    {
        return 0;
    }
    if ((m_numberOfImages < 1) || (m_numberOfImages > 77)) // smallest sequence has 77 images (0012)
    {
        return 0;
    }
}

bool Menu::checkInputSequence(int m_sequence) {
    if (!checker.checkDatatype(m_sequence))
    {
        return 0;
    }
    if ((m_sequence < 0) || (m_sequence > 20))
    {
        return 0;
    }
}

bool Menu::checkInputGameMode(int m_gameMode) {
    if (!checker.checkDatatype(m_gameMode))
    {
        return 0;
    }
    if ((m_gameMode < 1) || (m_gameMode > 2)) {
        return 0;
    }
}

bool Menu::checkInputGameStart(int m_gameStart) {
    if (!checker.checkDatatype(m_gameStart))
    {
        return 0;
    }
    if ((m_gameMode < 0) || (m_gameMode > 1)) {
        return 0;
    }
}