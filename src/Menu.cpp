#include "Menu.hpp"

Menu::Menu(/* args */)
{
}
Menu::~Menu()
{
}

void Menu::displayMenu() {
    promptPlayerName();
    promptNumberOfImages();
    promptSequence();
    promptGameMode();
    promptGameStart();
}

void Menu::promptPlayerName() {
    std::cout<<"Hallo Spieler, geben Sie ihren Namen ein: ";
    setPlayerName();
}

void Menu::promptNumberOfImages() {
    std::cout<<"\nWaehlen Sie wie viele Bilder Sie spielen moechten: ";
    setNumberOfImages();
}

void Menu::promptSequence() {
    std::cout<<"\nWaehlen Sie welche Sequenz Sie spielen moechten(0000-0020): ";
    setSequence();
}

void Menu::promptGameMode() {
    std::cout<<"\nWaehlen Sie den Spielmodus(1,2)";
    setGameMode();
}

void Menu::promptGameStart() {
    std::cout<<"\nWollen Sie das Spiel starten(ja:1, nein:0)?:";
    setGameStart();
}


void Menu::setPlayerName() {
    std::cin>>m_PlayerName;
    //checkInputInputName()
}

void Menu::setNumberOfImages() {
    std::cin>>m_numberOfImages;
    //checkInputInputImages()
}

void Menu::setSequence() {
    std::cin >> m_sequence;
    while(!checkInputSequence()) { //wenn input falsch, also 1 wiederhole
        std::cin >> m_sequence;
    }
}

void Menu::setGameMode() {
    std::cin>>m_gameMode;
    //checkInputInputMode()
}
void Menu::setGameStart() {
    std::cin>>m_gameStart;
    //checkInputInputStart()
}


// bool Menu::checkInputInputPlayerName();
// bool Menu::checkInputNumberOfImages();
bool Menu::checkInputSequence() {
    if(std::cin.fail()) {
        std::cout<<"\nGebe einen Integer ein: ";
        return 0;
    }
    else if(m_sequence < 0 || m_sequence < 20) {
        std::cout<<"\nGebe eine Zahl zwischen 0 - 20 ein: ";
        return 0;
    }
    else {
        return 1;
    }
}
// bool Menu::checkInputGameMode();
// bool Menu::checkInputGameMode();
// bool Menu::checkInputGameStart();


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