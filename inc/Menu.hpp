#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

class Menu {
public:
    Menu(/* args */);
    ~Menu();

    void displayMenu();

    void promptPlayerName();
    void promptNumberOfImages();
    void promptSequence();
    void promptGameMode();
    void promptGameStart();

    void setPlayerName();
    void setNumberOfImages();
    void setSequence();
    void setGameMode();
    void setGameStart();

    bool checkEmpty(std::string m_playerName);
    bool checkInteger(int integer);
    bool checkBool(bool boolean);

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
    int m_numberOfImages;
    int m_sequence;
    int m_gameMode;
    int m_gameStart;
};

#endif // MENU_HPP
