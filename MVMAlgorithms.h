#include <vector>
#include "SparseMatrixECSR.h"
using namespace std;

#ifndef ADVANCEDHIGHPERFORMANCECOMPUTING_MVMALGORITHMS_H
#define ADVANCEDHIGHPERFORMANCECOMPUTING_MVMALGORITHMS_H

vector<double> sparseMVMConcurrent(SparseMatrixECSR &mat, vector<double> &vec);

#endif //ADVANCEDHIGHPERFORMANCECOMPUTING_MVMALGORITHMS_H