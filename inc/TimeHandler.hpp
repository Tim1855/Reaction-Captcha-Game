#ifndef TIMEHANDLER_HPP
#define TIMEHANDLER_HPP

#include <chrono>

class TimeHandler {
public:
    TimeHandler();
    ~TimeHandler();

    void startTimer();
    double stopTimer();

private:
    std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMEHANDLER_HPP
