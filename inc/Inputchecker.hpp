#ifndef INPUTCHECKER_HPP
#define INPUTCHECKER_HPP

#include <iostream>
#include <type_traits>
#include <string>
#include <sstream>




// Base template
template<typename T>
int checkDataType(const std::string& input) {
    std::istringstream iss(input);
    T data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

// Specialization for int
template<>
int checkDataType<int>(const std::string& input) {
    std::istringstream iss(input);
    int data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

// Specialization for double
template<>
int checkDataType<double>(const std::string& input) {
    std::istringstream iss(input);
    double data;
    if (!(iss >> data) || !(iss.eof())) {
        return 0;
    }
    return 1;
}

// Specialization for std::string (any input is valid for std::string)
template<>
int checkDataType<std::string>(const std::string& input) {
    return 1; // Always valid for std::string
}

#endif // INPUTCHECKER_HPP