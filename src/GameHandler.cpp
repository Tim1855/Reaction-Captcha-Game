#include "GameHandler.hpp"
#include "GameMode1.hpp"
#include "GameMode2.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>

GameHandler::GameHandler() : m_currentGameMode(nullptr), m_numImagesToDisplay(0), m_imageClicked(false) {
}

GameHandler::~GameHandler() {
}

void GameHandler::initializeGame(const std::string& playerName, int numImages, int sequence, int gameMode) {
    m_playerName = playerName;
    m_numImagesToDisplay = numImages;
    m_sequence = sequence; // Speichern der Sequenznummer
    m_gameMode = gameMode;

    std::ostringstream sequenceStream;
    sequenceStream << std::setw(4) << std::setfill('0') << sequence;
    std::string sequenceString = sequenceStream.str();
    
    std::string imageFolderPath = "C:/appldev/Reaction-Captcha-Game/data/training/image_02/" + sequenceString;
    std::string bboxFolderPath = "C:/appldev/Reaction-Captcha-Game/data/label_02";

    if (m_gameMode == 1) {
        m_currentGameMode = std::make_unique<GameMode1>(imageFolderPath, bboxFolderPath);
    } else if (m_gameMode == 2) {
        m_currentGameMode = std::make_unique<GameMode2>(imageFolderPath, bboxFolderPath);
    }
    m_currentGameMode->setMouseCallback(&m_imageClicked);
}

void GameHandler::startGame() {
    m_currentGameMode->startMode(m_sequence, m_numImagesToDisplay);

    for (int i = 0; i < m_numImagesToDisplay; ++i) {
        m_currentGameMode->loadImageAndBoundingBox(m_sequence, i);
        displayNextImage();
        
        m_imageClicked = false;
        auto startTime = std::chrono::high_resolution_clock::now();
        while (!m_imageClicked) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
            if (duration >= 3) {
                std::cout << "Bild " << i + 1 << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
                m_reactionTimes.push_back(5.0); // Strafe von 5 Sekunden
                break;
            }
            cv::waitKey(30); // Kurzes Warten, um die Benutzerinteraktion zu überprüfen
        }
        if (m_imageClicked) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
            if (static_cast<GameMode1*>(m_currentGameMode.get())->lastClickInBoundingBox()) {
                std::cout << "Bild " << i + 1 << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
                m_reactionTimes.push_back(reactionTime);
            } else {
                std::cout << "Bild " << i + 1 << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
                m_reactionTimes.push_back(reactionTime + 5.0); // Strafe von 5 Sekunden
            }
        }
        cv::destroyAllWindows();
    }

    endGame();
}

void GameHandler::endGame() {
    std::cout << "Game ended." << std::endl;
    cv::destroyAllWindows();
    giveFeedback();
}

void GameHandler::displayNextImage() {
    if (m_currentGameMode) {
        m_currentGameMode->display();
    }
}

void GameHandler::giveFeedback() {
    std::cout << "Player: " << m_playerName << std::endl;
    std::cout << "Feedback: Spiel beendet." << std::endl;

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
        for (int i = 0; i < std::min(3, static_cast<int>(m_reactionTimes.size())); ++i) {
            if (m_reactionTimes[i] >= 0) {
                std::cout << i + 1 << ". " << m_reactionTimes[i] << " Sekunden" << std::endl;
            } else {
                std::cout << i + 1 << ". " << "Keine Reaktion : 5 Sekunden Strafe" << std::endl;
            }
        }
        std::cout << "Durchschnittliche Reaktionszeit: " << average << " Sekunden" << std::endl;
    } else {
        std::cout << "Keine Reaktionen registriert." << std::endl;
    }
}