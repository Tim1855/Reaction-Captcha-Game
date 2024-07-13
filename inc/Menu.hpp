#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

class Menu {
    public:
        void displayMenu();

        void setPlayerName();
        void setNumberOfImages();
        void setSequence();
        void setGameMode();
        void setGameStart();

        bool checkInputPlayerName();
        bool checkInputNumberOfImages();
        bool checkInputSequence();
        bool checkInputGameMode();
        bool checkInputGameStart();

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

#endif