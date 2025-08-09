#include "../include/commhelper.h"

RandomGenerator::RandomGenerator(): gen(std::random_device{}()) {
}

int RandomGenerator::getInt(const int min, const int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

double RandomGenerator::getDouble(const double min, const double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}
