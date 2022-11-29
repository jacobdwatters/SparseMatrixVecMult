EIGEN = /usr/include/eigen3

build:
	g++ -g -Wall -o main main.cpp SparseMatrixECSR.cpp LoadMatrix.cpp MVMAlgorithms.cpp RandomTensor.cpp -fopenmp -ffast-math -O3 -I${EIGEN}

run: build
	./main ${}

clean:
	rm -f main