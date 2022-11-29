#include <vector>
#include <Eigen/Sparse>

#ifndef SPARSEMATRIXVECTORMULT_SPARSEMATRIXECSR_H
#define SPARSEMATRIXVECTORMULT_SPARSEMATRIXECSR_H

using namespace std;

/**
 * Matrix stored in Extended Compressed Sparse Row (ECSR) Format.
 */
class SparseMatrixECSR {
public:
    vector<double> values;
    vector<int> rowIndices, colIndices;
    unsigned int numRows, numCols;
    SparseMatrixECSR();
    Eigen::SparseMatrix<double, Eigen::RowMajor> toEigMat();
    void printAttributes();
};


#endif //SPARSEMATRIXVECTORMULT_SPARSEMATRIXECSR_H
