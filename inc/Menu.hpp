#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>

class Menu {
public:
    Menu();
    ~Menu();

    void displayMenu();

    void setPlayerName();
    void setNumberOfImages();
    void setSequence();
    void setGameMode();
    void setGameStart();

    bool checkInputPlayerName(std::string m_PlayerName);
    bool checkInputNumberOfImages(int m_numberOfImages);
    bool checkInputSequence(int m_sequence);
    bool checkInputGameMode(int m_gameMode);
    bool checkInputGameStart(int m_gameStart);

    void promptPlayerName();
    void promptNumberOfImages();
    void promptSequence();
    void promptGameMode();
    void promptGameStart();

    std::string getPlayerName() const;
    int getNumberOfImages() const;
    int getSequence() const;
    int getGameMode() const;
    bool getGameStart() const;

private:
    std::string m_PlayerName;
    int m_numberOfImages;
    int m_sequence;
    int m_gameMode;
    bool m_gameStart;
};

#endif // MENU_HPP
