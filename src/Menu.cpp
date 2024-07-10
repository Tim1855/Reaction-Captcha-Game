#include "Menu.hpp"

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
    //checkInputName()
}

void Menu::setNumberOfImages() {
    std::cin>>m_numberOfImages;
    //checkInputImages()
}

void Menu::setSequence() {
    std::cin>>m_sequence;
    //checkInputSequence()
}

void Menu::setGameMode() {
    std::cin>>m_gameMode;
    //checkInputMode()
}
void Menu::setGameStart() {
    std::cin>>m_gameStart;
    //checkInputStart()
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