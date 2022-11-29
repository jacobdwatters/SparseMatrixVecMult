#include <vector>
#include "SparseMatrixECSR.h"
#include "MVMAlgorithms.h"
#include <iostream>


using namespace std;

vector<double> sparseMVMConcurrent(SparseMatrixECSR &mat, vector<double> &vec) {
    vector<double> product(mat.numRows);

    int row, col;
    double value;

    #pragma omp parallel for
    for(unsigned long int i=0; i<mat.values.size(); i++) {
        row = mat.rowIndices[i];
        col = mat.colIndices[i];
        value = mat.values[i];



        #pragma omp atomic
        product[row] += value*vec[col];
    }


    return product;
}