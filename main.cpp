#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "SparseMatrixECSR.h"
#include "MVMAlgorithms.h"
#include "LoadMatrix.h"
#include "RandomTensor.h"

using namespace std;

double total_time_ms = 0;

/**
 * Converts a dense vector to a Eigen VectorXd
 * @return
 */
Eigen::VectorXd vec2Eig(vector<double> vec) {
    Eigen::VectorXd eigVec = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(vec.data(), vec.size());
    return eigVec;
}


vector<double> time_spmvm(SparseMatrixECSR spMat, vector<double> vec) {
    cout << "Starting spmv multiplication..." << endl;

    auto start_time = chrono::high_resolution_clock::now();
    vector<double> spmvm = sparseMVMConcurrent(spMat, vec);
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time-start_time);
    double final_duration_ms = (double) duration.count()/1000;

    total_time_ms += final_duration_ms;

    printf("spmvm_concurrent: %.4f ms\n", final_duration_ms);
    return spmvm;
}

vector<double> time_spmvm_eig(Eigen::SparseMatrix<double, Eigen::RowMajor> mat, Eigen::VectorXd vec) {
    cout << "Starting spmv multiplication (Eigen)..." << endl;

    auto start_time = chrono::high_resolution_clock::now();
    Eigen::VectorXd spmvm_eig = mat*vec;
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time-start_time);
    double final_duration_ms = (double) duration.count()/1000;

    vector<double> spmvm(spmvm_eig.size());
    for(unsigned long int i=0; i<spmvm.size(); i++) { // Copy the vector to a boost vector
        spmvm[i] = spmvm_eig(i);
    }

    printf("spmvm_Eigen: %.4f ms\n", final_duration_ms);
    return spmvm;
}


/**
 * Computes the number of mismatches between two vectors.
 * @param v1 Vector 1.
 * @param v2 Vector 2.
 * @return The total number of mismatches between the two vectors. -1 if the vectors
 * are not the same size.
 */
int verify(vector<double> v1, vector<double> v2) {
    int numMismatch = 0;
    double tol = 1e-10; // A small tolerance for error due possible to floating point errors

    if(v1.size() != v2.size()) {
        numMismatch = -1;
    } else {
        for(unsigned long int i=0; i<v1.size(); i++) {
            if(abs(v1[i]-v2[i])>tol) {
                numMismatch+=1;
            }
        }
    }

    return numMismatch;
}


int main() {
    string fileList[] = {"./NLR.mtx", "./channel-500x100x100-b050.mtx", "./delaunay_n19.mtx"};
    RandomTensor RandTens;

    for(string file : fileList) {
        cout << "Loading file " << file << endl;
        auto start_time = chrono::high_resolution_clock::now();
        SparseMatrixECSR spMat = loadSymPat(file); // Load and fill sparse matrix from the specified file.
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time-start_time);
        double final_duration_ms = (double) duration.count()/1000;
        printf("Finished in %f ms\n\n", final_duration_ms);

        vector<double> vec = RandTens.getDenseVec(spMat.numRows); // Generate dense vector
        vector<double> spmvm_cc = time_spmvm(spMat, vec);

        start_time = chrono::high_resolution_clock::now();
        cout << "\nCopying to Eigen matrix/vector..." << endl;
        Eigen::SparseMatrix<double, Eigen::RowMajor> eigMat = spMat.toEigMat();
        Eigen::VectorXd eigVec = vec2Eig(vec);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end_time-start_time);
        final_duration_ms = (double) duration.count()/1000;
        printf("Finished in %f ms\n\n", final_duration_ms);

        vector<double> spmvm_ref = time_spmvm_eig(eigMat, eigVec);

        int numMismatch = verify(spmvm_cc, spmvm_ref);

        if(numMismatch==0) {
            cout << "\nResult matched reference library result!\n----------------------------------------------------\n\n";
        } else {
            cout << "\nError: result did NOT match reference library result with " << numMismatch << " mismatches.\n\n";
        }
    }

    cout << "Total execution time (for all sparse matrix vector multiplication(s)): " << total_time_ms << " ms" << endl;

    return 0;
}
