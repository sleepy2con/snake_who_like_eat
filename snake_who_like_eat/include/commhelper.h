#ifndef COMMHELPER_H
#define COMMHELPER_H
#include <random>

class RandomGenerator {
public:
    RandomGenerator();

    int getInt(int, int);

    double getDouble(double, double);

private:
    std::mt19937 gen;
};
#endif
