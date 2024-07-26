#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>

#include "GameHandler.hpp"
#include "GameMode1.hpp"
#include "GameMode2.hpp"
#include "Config.hpp"

GameHandler::GameHandler() {}

GameHandler::GameHandler(std::string playerName, int numberofImages, int sequence, int gameMode) : m_playerName{ playerName }, m_numberofImages{ numberofImages }, m_sequence{ sequence }, m_gameMode{ gameMode } {}

GameHandler::~GameHandler() {
}

void GameHandler::startGame() {
    GameMode* myGameMode = nullptr;
    if (m_gameMode == 1) {
        myGameMode = new GameMode1();
    }
    else if (m_gameMode == 2) {
        myGameMode = new GameMode2();
    }
    for (int image = 0; image < m_numberofImages; image++) {
        myGameMode->setClickStatus(NO_CLICK);
        myGameMode->loadImage(m_sequence, image);
        myGameMode->loadBoundingBoxes(m_sequence, image);
        myGameMode->display();
        myGameMode->updateTargetBox();
        myGameMode->setupCallback();
        auto startTime = std::chrono::high_resolution_clock::now();
        auto ConditionTime = startTime + std::chrono::seconds(3);
            while (std::chrono::high_resolution_clock::now() < ConditionTime) {
                cv::waitKey(1); // allow opencv to process mouse callback
                if (myGameMode->getClickStatus() != NO_CLICK) {
                    if (myGameMode->checkSpaceBarPress()) {
                        break;
                    }
                }
            }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
        if (reactionTime >= 3 && myGameMode->getClickStatus() == NO_CLICK) {
            std::cout << "Bild " << image << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
            data.images.push_back(image);
            data.reactionTimes.push_back(reactionTime);
        }
        else if (myGameMode->getClickStatus() == CORRECT_CLICK) {
            std::cout << "Bild " << image << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
            data.images.push_back(image);
            data.reactionTimes.push_back(reactionTime);
        }
        else if (myGameMode->getClickStatus() == INCORRECT_CLICK) {
            std::cout << "Bild " << image << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
            data.images.push_back(image);
            data.reactionTimes.push_back(reactionTime);
        }
    }
    delete myGameMode;
    endGame();
    giveFeedback();
}



void GameHandler::endGame() {
    cv::destroyAllWindows();
    std::cout << "Spiel beendet." << std::endl;
}


void GameHandler::giveFeedback() {
    std::cout << "Spieler: " << m_playerName << std::endl;
    sortReactionTimesAndImages(data);

    double sum = 0;
    for (double time : data.reactionTimes) {
        sum += time;
    }
    double average = sum / data.reactionTimes.size();

    std::cout << "Reaktionszeiten: " << std::endl;
    for (int i = 0; i < std::min(static_cast<int>(data.reactionTimes.size()), 3); i++) {
        if (data.reactionTimes[i] >= 0) {
            std::cout << "Bild " << data.images[i] << ": " << data.reactionTimes[i] << " Sekunden." << std::endl;
        }
    }
    std::cout << "Durchschnittliche Reaktionszeit: " << average << " Sekunden." << std::endl;
    data.images.clear();
    data.reactionTimes.clear();
}

void GameHandler::sortReactionTimesAndImages(ReactionData& data) {

    std::vector<size_t> indices(data.reactionTimes.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&data](size_t i, size_t j) {
        return data.reactionTimes[i] < data.reactionTimes[j];
        });

    std::vector<double> sortedReactionTimes(data.reactionTimes.size());
    std::vector<int> sortedImages(data.images.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sortedReactionTimes[i] = data.reactionTimes[indices[i]];
        sortedImages[i] = data.images[indices[i]];
    }

    data.reactionTimes = std::move(sortedReactionTimes);
    data.images = std::move(sortedImages);
}
