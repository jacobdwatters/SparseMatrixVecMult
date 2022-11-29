#include "SparseMatrixECSR.h"
#include <iostream>

/**
 * Constructs a sparse matrix stored in extended compressed sparse row format.
 */
SparseMatrixECSR::SparseMatrixECSR() {
    numRows = 0;
    numCols = 0;
    values.reserve(0);
    rowIndices.reserve(0);
    colIndices.reserve(0);
}


/**
 * Converts a ECSR matrix to an Eigen SparseMatrix.
 * @return An equivalent Eigen SparseMatrix.
 */
Eigen::SparseMatrix<double, Eigen::RowMajor> SparseMatrixECSR::toEigMat() {
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    tripletList.reserve(values.size());

    for(unsigned long int i=0; i<values.size(); i++) {
        tripletList.push_back(T(rowIndices[i], colIndices[i], values[i]));
    }

    Eigen::SparseMatrix<double> mat(numRows, numCols);
    mat.setFromTriplets(tripletList.begin(), tripletList.end());

    return mat;
}


/**
 * Prints the attributes of the ECSR matrix. Usefull for debugging.
 * That is, prints the values, rows and column indices.
 * WARNING: If this matrix is large, avoid calling this method.
 */
void SparseMatrixECSR::printAttributes() {
    cout << "Values: ";
    for(double v : values) {
        cout << v << "  ";
    }
    cout << "\nrowIndices: ";
    for(double v : rowIndices) {
        cout << v << "  ";
    }
    cout << "\ncolIndices: ";
    for(double v : colIndices) {
        cout << v << "  ";
    }
    cout << endl;
}