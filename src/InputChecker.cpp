#include "InputChecker.hpp"
#include <iostream>
#include <limits>

InputChecker::InputChecker() {
}

InputChecker::~InputChecker() {
}

template <typename T>
bool InputChecker::checkDatatype(T &input) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input from buffer
            return 0;
        }
        return 1;
    }

