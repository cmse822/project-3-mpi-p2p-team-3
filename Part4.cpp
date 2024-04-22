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
    for (int i = 0; i < 12; ++i) {
        comm_sizes[i] = j;
        j *= 2;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    int iterations = 100;
    int warmup_epoch = 10;

    for (int i = 0; i < 12; i++) {
        int num_elements_per_process = comm_sizes[i] / sizeof(int); 

        vector<int> data(num_elements_per_process);
        for (int k = 0; k < num_elements_per_process; k++) {
            data[k] = static_cast<int>(dis(gen) * 100); 
        }

        int shift = 2;
        int send_to = (rank + shift) % size;
        int recv_from = (rank - shift + size) % size;

        vector<int> recv_buffer(num_elements_per_process);

        MPI_Request send_request, recv_request;
        MPI_Status status;

        for (int k = 0; k < warmup_epoch; k++) {
            MPI_Isend(data.data(), num_elements_per_process, MPI_INT, send_to, 0, MPI_COMM_WORLD, &send_request);
            MPI_Irecv(recv_buffer.data(), num_elements_per_process, MPI_INT, recv_from, 0, MPI_COMM_WORLD, &recv_request);
            MPI_Wait(&send_request, &status);
            MPI_Wait(&recv_request, &status);
        }

        double start_time = MPI_Wtime();

        for (int k = 0; k < iterations; k++) {
            MPI_Isend(data.data(), num_elements_per_process, MPI_INT, send_to, 0, MPI_COMM_WORLD, &send_request);
            MPI_Irecv(recv_buffer.data(), num_elements_per_process, MPI_INT, recv_from, 0, MPI_COMM_WORLD, &recv_request);
            MPI_Wait(&send_request, &status);
            MPI_Wait(&recv_request, &status);
        }

        double end_time = MPI_Wtime();
        double elapsed_time = end_time - start_time;

        if (rank == 0) {
            long bytes = num_elements_per_process * sizeof(int) * iterations;
            cout << "Message size: " << comm_sizes[i] << " bytes, ";
            cout << "Time per transfer: " << elapsed_time / (2.0 * iterations) << " seconds, ";
            cout << "Bandwidth: " << (bytes / elapsed_time) / 1e6 << " MB/s" << endl;
        }
    }

    MPI_Finalize();
    return 0;
}