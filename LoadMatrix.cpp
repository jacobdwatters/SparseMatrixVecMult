#include <string>
#include <fstream>
#include "SparseMatrixECSR.h"
#include "RandomTensor.h"
#include "LoadMatrix.h"


/**
 * Loads a sparse matrix stored in MatrixMarket pattern symmetric format from a specified file.
 * WARNING: this function makes a whole lot of assumptions about the format of the file contents with very few checks if the
 * content actually adheres to the format.
 * @param fileName File name, including the extension, of file containing the matrix.
 * @return The matrix in extended compressed sparse row format ECSR.
 */
SparseMatrixECSR loadSymPat(string& fileName) {
    ifstream file(fileName);
    string line;
    SparseMatrixECSR spMat;

    if(file.is_open()) {
        int numRows = 0, numCols = 0, numLines = 0;

        // Ignore comments
        while (file.peek() == '%') file.ignore(2048, '\n');
        file >> numRows >> numCols >> numLines;

        double value;
        int row, col;
        vector<vector<double>> arr(10000, vector<double>(10000));
        vector<double> rowIndices(2*numLines);

        // Reserve the appropriate space in each vector.
        spMat.values.resize(2*numLines);
        spMat.rowIndices.resize(2*numLines);
        spMat.colIndices.resize(2*numLines);

        spMat.numRows = numRows;
        spMat.numCols = numCols;

        for (int i = 0; i<2*numLines-1; i+=2) { // Read row and column indices for each value
            file >> row >> col;
            value = RandomTensor::getRandValue();

            spMat.values[i] = value;
            spMat.colIndices[i] = col - 1;
            spMat.rowIndices[i] = row - 1; // Add one to the row count for this row

            if(row!=col) {
                // Then also insert on other side of diagonal since matrix is symmetric.
                spMat.values[i + 1] = value;
                spMat.colIndices[i + 1] = row - 1;
                spMat.rowIndices[i + 1] = col - 1; // Add one to the row count for this row
            }
        }

        file.close();
    }

    return spMat;
}