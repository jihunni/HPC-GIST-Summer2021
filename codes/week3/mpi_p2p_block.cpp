#include <iostream>
#include <mpi.h>		// MPI header file
#define MASTER 0

using namespace std;

int main(int argc, char **argv) {
  int nprocs, rank;

  // initialize for MPI
  MPI_Init(&argc, &argv);
  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
  // get the rank = this process's number (ranges from 0 to nprocs - 1)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // print a greeting
  cout << "Hello from process rank = " << rank << endl;

  int val = 0;
  // master send value to workers
  if (rank == MASTER) {
    val = 100;
    for (int dest_rank = 1; dest_rank < nprocs; dest_rank++) {
      MPI_Send(&val, 1, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
    }
    cout << "Process rank = " << rank << " has a value of " << val << endl;
  }
  // workers get the message
  else {
    MPI_Status status;
    MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    cout << "Process rank = " << rank << " has a value of " << val << endl;
    val = val + rank;
    cout << "Process rank = " << rank << " has a updated value of " << val << endl;
  }
    
  // clean up for MPI
  MPI_Finalize();   // C style

  return 0;
}

