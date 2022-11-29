#include <vector>
#include <random>
#include "RandomTensor.h"
using namespace std;

constexpr static const double MIN = 0.1;
constexpr static const double MAX = 4.9;
uniform_real_distribution<double> unif(MIN, MAX);
default_random_engine re;

/**
 * Generates a random number in [0.1, 4.9].
 * @return The random number in [0.1, 4.9].
 */
double RandomTensor::getRandValue() {
    return unif(re);
}


vector<double> RandomTensor::getDenseVec(int m) {
    vector<double> randVec(m);

    for(unsigned long int i=0; i<randVec.size(); i++) {
        randVec[i] = getRandValue();
    }

    return randVec;
}
