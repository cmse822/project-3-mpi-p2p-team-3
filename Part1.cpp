#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h" 

using namespace std; 

int main(int argc, char *argv[]){

    // int numtasks, rank; 
    // double start_time, end_time; 

    // MPI_Init(&argc, &argv); 
    // MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int Sizes[12]; 
    int iterations = 100;

    int j = 2; 
    for(int i = 0; i < 12; ++i){
        Sizes[i] = j;
        j *= 2; 
    }

    start_time = MPI_Wtime();
    for(int iter = 0; iter < iterations; ++iter){
        // if (rank  == 0) {
        //     dest =  1;
        //     source = 1;
        //     MPI_Send(&outmessage);
        //     MPI_Recv(&inmessage);
        // }

        // else if( rank  == 1){
        //     dest =  0;
        //     source = 0;
        //     MPI_Recv(&inmessage);
        //     MPI_Send(&outmessage);
        // }
    }
    end_time = MPI_Wtime();



    // cout << "Runtime: " <<  end_time - start_time << endl; 
    // MPI_Finalize(); 



    return 0; 
}