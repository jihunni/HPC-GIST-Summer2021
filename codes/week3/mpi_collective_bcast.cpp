# include <iostream>
# include <cstdlib>	// has exit(), etc.
# include <ctime>
# include "mpi.h"	// MPI header file

using namespace std;

//****************************************************************************80
int main (int argc, char **argv)
//****************************************************************************80
{
  int nprocs, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int data = 0;
  cout << "Before Bcast, data = " << data << " in rank = " << rank << endl;

  if (rank == 0) {	// root
    data = 100;
  }

  MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);	// MPI_Bcast
  cout << "After Bcast, data = " << data << " in rank = " << rank << endl;

  MPI_Finalize();
  return 0;
}

