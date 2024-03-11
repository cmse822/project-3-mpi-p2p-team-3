#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);

    int rank,size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::ofstream outfile;
    if(rank == 0){
        outfile.open("ring_shift_nonblocking_timings.csv");
        outfile << "MessageSize(Bytes), Iteration, TimeTaken(s)\n";
    }

    for(int exp = 1; exp <= 12; ++exp){
        int msg_size = std::pow(2,exp);
        std::vector<char> send_buffer(msg_size, 'a');
        std::vector<char> recv_buffer(msg_size);

        int next = (rank + 1) % size;
        int prev = (rank + size - 1) % size; 

        MPI_Request send_request, recv_request;
        MPI_Status status;


        for(int i= 0; i < 100; ++i){
            double start_time = MPI_Wtime();

            MPI_Isend(send_buffer.data(), msg_size, MPI_CHAR, next, 0, MPI_COMM_WORLD, &send_request);
            MPI_Irecv(recv_buffer.data(), msg_size, MPI_CHAR, prev, 0, MPI_COMM_WORLD, &recv_request);

            MPI_Wait(&send_request, &status);
            MPI_Wait(&recv_request, &status);

            double end_time = MPI_Wtime();
            double time_taken = end_time - start_time;

            if(rank == 0){
                double recv_time;
                MPI_Reduce(&time_taken, &recv_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
                outfile << msg_size << "," << i << "," << recv_time << "\n";

            }else{
                MPI_Reduce(&time_taken, NULL, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
            }
        }
    }

    if (rank == 0){
        outfile.close();
    }

    MPI_Finalize();
    return 0;
}