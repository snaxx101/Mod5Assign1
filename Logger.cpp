#include "Logger.h"

Logger::Logger(const std::string &filename) {
    log.open(filename);
}

void Logger::write(const std::string &message) {
    log << message << std::endl;
}
