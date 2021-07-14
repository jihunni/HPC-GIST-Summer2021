#include <iostream>
#include <mpi.h>		// MPI header file

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

  double d = 100.0;
  int tag = 1;

  // master send value to workers
  if (rank == 0) {
    // synchronous send: return when the destination has started
    // to receive the message
    MPI_Recv(&d, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
    MPI_Send(&d, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
  }
  // workers get the message
  else {
    MPI_Recv(&d, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
    MPI_Send(&d, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
  }
    
  // clean up for MPI
  MPI_Finalize();   // C style

  return 0;
}

