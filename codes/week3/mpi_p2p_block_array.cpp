#include <iostream>
#include <mpi.h>		// MPI header file
#define MASTER 0
#define LEN_VAL 100

using namespace std;

int main(int argc, char **argv) {
  int nprocs, rank;

  // initialize for MPI
  MPI_Init(&argc, &argv);
  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
  // get the rank = this process's number (ranges from 0 to nprocs - 1)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // MPI status
  MPI_Status status;

  // consider chunk size by nprocs
  int val[LEN_VAL] = {0};
  int chunk_size = LEN_VAL / nprocs;    // assume no remainder
  int offset = 0, partial_sum = 0, total_sum = 0;

  // master 
  if (rank == MASTER) 
  {
    // master initializes all elements of the array
    for (int i=0; i<LEN_VAL; i++)
      val[i] = i+1;

    // master sends chunk of the array
    for (int dest_rank = 1; dest_rank < nprocs; dest_rank++) {
      offset = dest_rank * chunk_size;
      MPI_Send(&val[offset], chunk_size, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
    }

    // sum of chunk elements on master process
    cout << "Process rank = " << rank << " has a value of ";
    for (int i=0; i < chunk_size; i++) {
      cout << val[i] << " ";
      total_sum += val[i];
    }
    cout << endl;

    // master receives each partial sum from a worker and add it to total_sum
    for (int src_rank = 1; src_rank < nprocs; src_rank++) {
      MPI_Recv(&partial_sum, 1, MPI_INT, src_rank, 0, MPI_COMM_WORLD, &status);
      total_sum += partial_sum;
    }

    // print out total sum
    cout << "Total sum of the array elements is " << total_sum << endl; 
  }
  // workers
  else 
  {
    // each worker receives the array chunk (it goes to index 0 ~ chink size)
    MPI_Recv(&val, chunk_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    cout << "Process rank = " << rank << " has a value of ";

    // calculate partial sum
    for (int i=0; i<chunk_size; i++) {
      cout << val[i] << " ";
      partial_sum += val[i];
    }
    cout << endl;

    // each worker send the partial sum to master
    MPI_Send(&partial_sum, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
  }
    
  // clean up for MPI
  MPI_Finalize();

  return 0;
}

