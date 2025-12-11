//
// Created by Marcin Lusa on 10/12/2025.
//

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

// ANSI color codes
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

std::string GetCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

void Logger::Info(const std::string &message) {
    std::cout << COLOR_GREEN << "[INFO] [" << GetCurrentDateTime() << "] "
              << message << COLOR_RESET << std::endl;
}

void Logger::Error(const std::string &message) {
    std::cerr << COLOR_RED << "[ERROR] [" << GetCurrentDateTime() << "] "
              << message << COLOR_RESET << std::endl;
}
