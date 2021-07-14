#include <iostream>
#include <mpi.h>		// MPI header file
#define MASTER 0
#define N 100000000

using namespace std;

int main(int argc, char **argv) {
  int nprocs, rank; 
  long long int start_val, end_val, total_sum = 0, partial_sum = 0;

  // initialize for MPI
  MPI_Init(&argc, &argv);
  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
  // get the rank = this process's number (ranges from 0 to nprocs - 1)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // MPI status
  MPI_Status status;

  // each process do "partial sum" with
  start_val = rank * (N/nprocs) + 1;
  end_val = (rank+1) * (N/nprocs);
  for (int val=start_val; val<=end_val; val++) 
    partial_sum += val;
  cout << "rank " << rank << " calculated partial_sum " << partial_sum << endl;
  
  // master 
  if (rank == MASTER) 
  {
    // save current partial_sum into total_sum
    total_sum = partial_sum;

    // master receives each partial sum from a worker and add it to total_sum
    for (int src_rank = 1; src_rank < nprocs; src_rank++) {
      MPI_Recv(&partial_sum, 1, MPI_LONG_LONG_INT, src_rank, 0, MPI_COMM_WORLD, &status);
      cout << "master received partial_sum " << partial_sum << " from a source rank " << src_rank << endl;
      total_sum += partial_sum;
    }

    // print out total sum
    cout << "Total sum of the array elements is " << total_sum << endl; 
  }
  // workers
  else 
  {
    // each worker send the partial sum to master destination
    MPI_Send(&partial_sum, 1, MPI_LONG_LONG_INT, MASTER, 0, MPI_COMM_WORLD);
  }
    
  // clean up for MPI
  MPI_Finalize();

  return 0;
}
