#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>

using namespace std;


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int comm_sizes[12]; 

    int j = 2; 
    for(int i = 0; i < 12; ++i){
        comm_sizes[i] = j;
        j *= 2; 
    }

    random_device rd;  // Provides a seed for the random number engine
    mt19937 gen(rd()); // Mersenne Twister 19937 generator, seeded with rd
    uniform_real_distribution<> dis(0.0, 1.0); // Distribution for doubles between 0.0 and 1.0
    int iterations = 100;

    int warmup_epoch = 10;

    for(int i = 0;i < 12;i++){

        // Number of elements per process
        int num_elements_per_process = comm_sizes[i];

        // Initialize data
        std::vector<int> data(num_elements_per_process);
        for (int i = 0; i < num_elements_per_process; i++) {
            data[i] = dis(gen);
        }

        int shift = 2; // Number of positions to shift, fixed now, you may change it

        // Send and receive data
        int send_to = (rank + shift) % size;
        int recv_from = (rank - shift + size) % size;

        std::vector<int> recv_buffer(num_elements_per_process);

        for (int i = 0;i < warmup_epoch;i++){
            MPI_Sendrecv(data.data(), num_elements_per_process, MPI_INT, send_to, 0,
                    recv_buffer.data(), num_elements_per_process, MPI_INT, recv_from, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        double start_time, stop_time;

        start_time = MPI_Wtime();

        for (int i = 0; i < iterations; i++) {
            MPI_Sendrecv(data.data(), num_elements_per_process, MPI_INT, send_to, 0,
                    recv_buffer.data(), num_elements_per_process, MPI_INT, recv_from, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        stop_time = MPI_Wtime();
        double elapsed_time = stop_time - start_time;

        long bytes = num_elements_per_process * sizeof(int);

        if (rank == 0) {
           // cout << "Message size: " << bytes << " bytes" << endl;
           // cout << "Time Per transfer: " << elapsed_time / (2.0*(double)iterations) << " seconds" << endl;
           // cout << "Bandwidth: " << (bytes * iterations) / (elapsed_time) << "byte/s" << endl;
            cout << bytes << ",";
            cout << elapsed_time / (2.0*(double)iterations) << ",";
            cout << (bytes * iterations) / (elapsed_time) << endl;

        }
        
    }
    MPI_Finalize();
    return 0;
}