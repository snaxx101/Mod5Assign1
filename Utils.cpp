#include "Utils.h"

int randomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double randomDouble(double min, double max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}
