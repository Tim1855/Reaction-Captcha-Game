#include "TimeHandler.hpp"

TimeHandler::TimeHandler() {
}

TimeHandler::~TimeHandler() {
}

void TimeHandler::startTimer() {
    startTime = std::chrono::high_resolution_clock::now();
}

double TimeHandler::stopTimer() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    return elapsed.count();
}

void TimeHandler::delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
