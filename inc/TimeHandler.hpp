#ifndef TIMEHANDLER_HPP
#define TIMEHANDLER_HPP

#include <chrono>
#include <thread>

class TimeHandler {
public:
    TimeHandler();
    ~TimeHandler();

    void startTimer();
    double stopTimer();
    void delay(int milliseconds); // Neue Methode zum Verzögern

private:
    std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMEHANDLER_HPP
