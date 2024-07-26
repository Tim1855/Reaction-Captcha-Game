#ifndef INPUTCHECKER_HPP
#define INPUTCHECKER_HPP

#include <iostream>
#include <type_traits>
#include <string>
#include <sstream>




template<typename T>
int checkDataType(const std::string& input) {
    std::istringstream iss(input);
    T data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

template<>
int checkDataType<int>(const std::string& input) {
    std::istringstream iss(input);
    int data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

template<>
int checkDataType<double>(const std::string& input) {
    std::istringstream iss(input);
    double data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

template<>
int checkDataType<std::string>(const std::string& input) {
    return 1;
}
#endif // INPUTCHECKER_HPP