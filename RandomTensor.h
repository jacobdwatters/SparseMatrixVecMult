#ifndef ADVANCEDHIGHPERFORMANCECOMPUTING_RANDOMTENSOR_H
#define ADVANCEDHIGHPERFORMANCECOMPUTING_RANDOMTENSOR_H

#include <vector>
#include <random>

using namespace std;

class RandomTensor {
public:
    static vector<double> getDenseVec(int m);
    static double getRandValue();
};


#endif //ADVANCEDHIGHPERFORMANCECOMPUTING_RANDOMTENSOR_H
