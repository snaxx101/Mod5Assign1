#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
    std::ofstream log;
public:
    Logger(const std::string &filename);
    void write(const std::string &message);
};

#endif
