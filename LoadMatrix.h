#include <string>
#include "SparseMatrixECSR.h"

#ifndef ADVANCEDHIGHPERFORMANCECOMPUTING_LOADMATRIX_H
#define ADVANCEDHIGHPERFORMANCECOMPUTING_LOADMATRIX_H

/**
 * Loads a symmetric pattern matrix stored in MatrixMarket pattern symmetric format.
 *
 * WARNING: this function makes a whole lot of assumptions about the format of the file contents with very few checks if the
 * content actually adheres to said format.
 *
 * @param fileName File name, including the extension, of file containing the matrix.
 * @return The matrix in extended compressed sparse row format ECSR.
 */
SparseMatrixECSR loadSymPat(string& fileName);

#endif //ADVANCEDHIGHPERFORMANCECOMPUTING_LOADMATRIX_H

