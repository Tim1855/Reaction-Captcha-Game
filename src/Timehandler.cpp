#include "TimeHandler.hpp"

TimeHandler::TimeHandler() : m_startTime() {}

void TimeHandler::start() {
    m_startTime = std::chrono::high_resolution_clock::now();
}

double TimeHandler::stop() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_startTime).count();
    return duration / 1000.0;
}
