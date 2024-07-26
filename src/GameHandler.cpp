#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "GameHandler.hpp"
#include "GameMode1.hpp"
#include "GameMode2.hpp"
#include "Config.hpp"

GameHandler::GameHandler() {}

GameHandler::GameHandler(std::string playerName, int numberofImages, int sequence, int gameMode) : m_playerName{ playerName }, m_numberofImages{ numberofImages }, m_sequence{ sequence }, m_gameMode{ gameMode } {}

GameHandler::~GameHandler() {
}

void GameHandler::startGame() {
    if (m_gameMode == 1) {
        GameMode1 myGameMode;
        for (int image = 0; image < m_numberofImages; image++) {
            myGameMode.loadImage(m_sequence, image);
            myGameMode.loadBoundingBoxes(m_sequence, image);
            myGameMode.display();
            myGameMode.setupCallback();
            myGameMode.setImageClicked(false);
            auto startTime = std::chrono::high_resolution_clock::now();
            while (!myGameMode.getImageClicked()) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                m_duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

                cv::waitKey(30); // Wait briefly to check for user interaction

                if (myGameMode.getImageClicked()) {
                    break;
                }
                else if (m_duration >= 3) {
                    std::cout << "Bild " << image << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(5.0); // 5 seconds penalty
                    break;
                }
            }

            if (myGameMode.getImageClicked()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
                if (myGameMode.lastClickInBoundingBox()) {
                    std::cout << "Bild " << image << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
                    m_reactionTimes.push_back(reactionTime);
                }
                else {
                    std::cout << "Bild " << image << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(reactionTime + 5.0); // Strafe von 5 Sekunden
                }
            }
        }
    }
    else {
        GameMode2 myGameMode;
        for (int image = 0; image < m_numberofImages; image++) {
            myGameMode.loadImage(m_sequence, image);
            myGameMode.loadBoundingBoxes(m_sequence, image);
            myGameMode.display();
            myGameMode.updateTargetBox();
            myGameMode.setupCallback();
            myGameMode.setSpaceBarPress(false);
            auto startTime = std::chrono::high_resolution_clock::now();
            while (!myGameMode.getSpaceBarPress()) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                m_duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

                myGameMode.checkSpaceBarPress();

                if (myGameMode.getSpaceBarPress()) {
                    break;
                }

                if (m_duration >= 3) {
                    std::cout << "Bild " << image << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(5.0); // 5 seconds penalty
                    break;
                }
            }

            if (myGameMode.getSpaceBarPress()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
                if (myGameMode.lastClickInBoundingBox()) {
                    std::cout << "Bild " << image << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
                    m_reactionTimes.push_back(reactionTime);
                }
                else {
                    std::cout << "Bild " << image << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(reactionTime + 5.0); // Strafe von 5 Sekunden
                }
            }
        }
    }
    endGame();
    giveFeedback();
}


void GameHandler::endGame() {
    cv::destroyAllWindows();
    std::cout << "Game ended." << std::endl;
}

void GameHandler::giveFeedback() {
    std::cout << "Player: " << m_playerName << std::endl;

    if (!m_reactionTimes.empty()) {
        std::sort(m_reactionTimes.begin(), m_reactionTimes.end(), [](double a, double b) { return a > 0 && (b < 0 || a < b); });

        double sum = 0;
        int count = 0;
        for (double time : m_reactionTimes) {
            sum += time; // Add all times including penalties
            if (time >= 0) {
                count++;
            }
        }
        double average = (count > 0) ? sum / m_reactionTimes.size() : 0; // Include penalties in average calculation

        std::cout << "Beste Reaktionszeiten:" << std::endl;
        for (int i = 0; i < std::min(3, static_cast<int>(m_reactionTimes.size())); i++) {
            if (m_reactionTimes[i] >= 0) {
                std::cout << i << ". " << m_reactionTimes[i] << " Sekunden" << std::endl;
            }
            else {
                std::cout << i << ". " << "Keine Reaktion : 5 Sekunden Strafe" << std::endl;
            }
        }
        std::cout << "Durchschnittliche Reaktionszeit: " << average << " Sekunden" << std::endl;
    }
    else {
        std::cout << "Keine Reaktionen registriert." << std::endl;
    }
}
