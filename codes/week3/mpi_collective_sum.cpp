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
  
  MPI_Reduce(&partial_sum, &total_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
  if (rank == MASTER)
    cout << "Total sum of the array elements is " << total_sum << endl; 
    
  // clean up for MPI
  MPI_Finalize();

  return 0;
}
