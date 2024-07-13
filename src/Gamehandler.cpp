#include "GameHandler.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

GameHandler::GameHandler() : currentGameMode(nullptr), numImagesToDisplay(0) {
}

GameHandler::~GameHandler() {
}

void GameHandler::initializeGame(const std::string& playerName, int numImages, int sequence, int gameMode) {
    this->playerName = playerName;
    numImagesToDisplay = numImages;
    loadImages(sequence);
    mouseHandler.setWindowName("Game Window"); // Fenster erstellen und Maus-Callback setzen
    if (gameMode == 1) {
        std::ostringstream sequenceStream;
        sequenceStream << std::setw(4) << std::setfill('0') << sequence;
        std::string sequenceString = sequenceStream.str();
        std::string imageFolderPath = "C:/appldev/Reaction-Captcha-Game/data/training/image_02/" + sequenceString;
        std::string bboxFolderPath = "C:/appldev/Reaction-Captcha-Game/data/label_02";
        currentGameMode = std::make_unique<GameMode1>(imageFolderPath, bboxFolderPath);
        currentGameMode->startMode();
    } else if (gameMode == 2) {
        currentGameMode = std::make_unique<GameMode2>();
        currentGameMode->startMode();
    }
}

void GameHandler::startGame() {
    for (int i = 0; i < numImagesToDisplay; ++i) {
        displayNextImage();
        auto* gameMode1 = dynamic_cast<GameMode1*>(currentGameMode.get());
        if (gameMode1) {
            gameMode1->loadImageAndBoundingBox(gameMode1->getCurrentSequence(), i);
            auto startTime = std::chrono::high_resolution_clock::now();
            handleUserInput();
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> reactionTime = endTime - startTime;
            processReaction(i, reactionTime.count());
        }
    }

    endGame();
}

void GameHandler::endGame() {
    std::cout << "Game ended." << std::endl;
    cv::destroyAllWindows();
    giveFeedback();
}

void GameHandler::loadImages(int sequence) {
    std::ostringstream sequenceStream;
    sequenceStream << std::setw(4) << std::setfill('0') << sequence;
    std::string sequenceString = sequenceStream.str();
    std::cout << "Loading images from sequence " << sequenceString << std::endl;
}

void GameHandler::handleUserInput() {
    int x = -1, y = -1;
    std::cout << "Waiting for user input..." << std::endl;

    mouseHandler.setClickCallback([&x, &y](int clickX, int clickY) {
        x = clickX;
        y = clickY;
    });

    auto start = std::chrono::high_resolution_clock::now();
    while (x == -1 && y == -1) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if (elapsed.count() >= 3.0) {
            std::cerr << "Too slow! Moving to the next image." << std::endl;
            processReaction(-1, 3.0); // Timeout
            return;
        }
        int key = cv::waitKey(1);
        if (key == 27) { // ESC key to exit
            std::cerr << "Window closed by user." << std::endl;
            exit(0);
        }
    }

    if (currentGameMode) {
        currentGameMode->processInput(x, y);
    }
}

void GameHandler::displayNextImage() {
    if (currentGameMode) {
        currentGameMode->display();
    }
}

void GameHandler::processReaction(int imageIndex, double reactionTime) {
    reactionTimes.push_back(std::make_tuple(imageIndex, reactionTime));
}

void GameHandler::giveFeedback() {
    std::cout << "Player: " << playerName << std::endl;
    double totalReactionTime = 0.0;
    for (const auto& [index, time] : reactionTimes) {
        totalReactionTime += time;
        std::cout << "Image " << index << ": " << time << " seconds" << std::endl;
    }
    double avgReactionTime = totalReactionTime / reactionTimes.size();
    std::cout << "Average reaction time: " << avgReactionTime << " seconds" << std::endl;

    std::sort(reactionTimes.begin(), reactionTimes.end(), [](const auto& a, const auto& b) {
        return std::get<1>(a) < std::get<1>(b);
    });

    std::cout << "Top 3 reaction times:" << std::endl;
    for (int i = 0; i < std::min(3, static_cast<int>(reactionTimes.size())); ++i) {
        std::cout << "Image " << std::get<0>(reactionTimes[i]) << ": " << std::get<1>(reactionTimes[i]) << " seconds" << std::endl;
    }
}
