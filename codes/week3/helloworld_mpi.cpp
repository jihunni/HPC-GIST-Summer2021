#include <iostream>
#include <mpi.h>		// MPI header file
#define MASTER 0

using namespace std;

int main(int argc, char **argv) {
  int nprocs, rank;

  // initialize for MPI (should come before any other calls to MPI routines)
  MPI_Init(&argc, &argv);   // C style
  // MPI::Init(argc, argv);    // C++ style

  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);   // C style
  // nprocs = MPI::COMM_WORLD.Get_size();      // C++ style

  // get the rank = this process's number (ranges from 0 to nprocs - 1)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);     // C style
  // rank = MPI::COMM_WORLD.Get_rank();        // C++ style

  // print a greeting
  cout << "Hello from process " << rank << " of " << nprocs << endl;

  // clean up for MPI
  MPI_Finalize();   // C style
  // MPI::Finalize();  // C++ style

  return 0;
}

