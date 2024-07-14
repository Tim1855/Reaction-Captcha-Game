#ifndef TIMEHANDLER_HPP
#define TIMEHANDLER_HPP

#include <chrono>

class TimeHandler {
public:
    TimeHandler();
    void start();
    double stop();

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
};

#endif // TIMEHANDLER_HPP
