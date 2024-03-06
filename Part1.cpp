/*
Compile with: mpicxx -o Part1.exe Part1.cpp
Execute with: mpiexec -n 2 Part1.exe 
*/

#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <fstream>
#include "mpi.h" 

using namespace std; 

int main(int argc, char *argv[]){

    MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status stat;

    random_device rd;  // Provides a seed for the random number engine
    mt19937 gen(rd()); // Mersenne Twister 19937 generator, seeded with rd
    uniform_real_distribution<> dis(0.0, 1.0); // Distribution for doubles between 0.0 and 1.0

    const int N  = 25;

    int comm_sizes[N]; 
    int iterations = 100;
    int warmup_epoch = 10;
    
    ofstream out_file("Part1_Data.txt");
    out_file << "Bytes,TransferTime,Bandwidth" << endl;

    int j = 2; 
    for(int i = 0; i < N; ++i){
        comm_sizes[i] = j;
        j *= 2; 
    }

    for (int i = 0; i < N;i++){
        auto alloc_size = comm_sizes[i];
        double *ptr = new double[alloc_size];

        // randomly initialize the array
        for (int i = 0; i < alloc_size; i++){
            ptr[i] = dis(gen);
        }

        int node_tag1 = 1;
        int node_tag2 = 2;

        // the first 10 loops are used for warmup
        for(int i = 0; i < warmup_epoch;i++) {
            if (rank == 0) {
                MPI_Send(ptr, alloc_size, MPI_DOUBLE, 1, node_tag1, MPI_COMM_WORLD);
                MPI_Recv(ptr, alloc_size, MPI_DOUBLE, 1, node_tag2, MPI_COMM_WORLD, &stat);
            } else {
                MPI_Recv(ptr, alloc_size, MPI_DOUBLE, 0, node_tag1, MPI_COMM_WORLD, &stat);
                MPI_Send(ptr, alloc_size, MPI_DOUBLE, 0, node_tag2, MPI_COMM_WORLD);
            }
        }

        double start_time, stop_time;
        start_time = MPI_Wtime();

        for(int i = 0; i < iterations; i++) {
            if (rank == 0) {
                MPI_Send(ptr, alloc_size, MPI_DOUBLE, 1, node_tag1, MPI_COMM_WORLD);
                MPI_Recv(ptr, alloc_size, MPI_DOUBLE, 1, node_tag2, MPI_COMM_WORLD, &stat);
            } else {
                MPI_Recv(ptr, alloc_size, MPI_DOUBLE, 0, node_tag1, MPI_COMM_WORLD, &stat);
                MPI_Send(ptr, alloc_size, MPI_DOUBLE, 0, node_tag2, MPI_COMM_WORLD);
            }
        }

        stop_time = MPI_Wtime();
        double elapsed_time = stop_time - start_time;

        long bytes = alloc_size * sizeof(double);

        if (rank == 0) {
            cout << "Message size: " << bytes << " bytes" << endl;
            cout << "Time Per transfer: " << elapsed_time / (2.0*(double)iterations) << " seconds" << endl;
            cout << "Bandwidth: " << (bytes * iterations) / (elapsed_time) << "byte/s" << endl;
            out_file << bytes << "," << elapsed_time / (2.0*(double)iterations) << "," << (bytes * iterations) / (elapsed_time) <<  endl;
        }

        delete[] ptr;

    }
 
    out_file.close();
    MPI_Finalize(); 

    return 0; 
}