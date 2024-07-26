#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

class Menu {
public:
    Menu();
    ~Menu();


    void displayMenu();


    const void promptPlayerName();
    const void promptNumberOfImages();
    const void promptSequence();
    const void promptGameMode();
    const void promptGameStart();


    void setPlayerName();
    void setNumberOfImages();
    void setSequence();
    void setGameMode();
    void setGameStart();

    bool checkNumberOfImages(int m_numberOfImages);
    bool checkSequence(int m_sequence);
    bool checkGameMode(int m_gameMode);
    bool checkGameStart(int m_gameStart);


    std::string getPlayerName() const;
    int getNumberOfImages() const;
    int getSequence() const;
    int getGameMode() const;
    int getGameStart() const;

private:
    std::string m_playerName;
    std::string m_input;
    int m_numberOfImages;
    int m_sequence;
    int m_gameMode;
    int m_gameStart;
};

#endif
