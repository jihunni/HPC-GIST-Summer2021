# include <iostream>
# include <cstdlib>	// has exit(), etc.
# include <ctime>
# include "mpi.h"	// MPI header file

using namespace std;

int main (int argc, char **argv)
{
  int data_array[8] = {};
  int recv_buffer[8] = {};
  int nprocs, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {	// root
    for (int i=0; i<8; i++) {
      data_array[i] = 100+i;
    }
  }

  int send_count = 2;
  int recv_count = 2;

  cout << "Before Scatter, data_array = ";
  for (int j=0; j<8; j++) {cout << data_array[j] << " ";}
  cout << " in rank = " << rank << endl;
  cout << "Before Scatter, recv_buffer = ";
  for (int j=0; j<8; j++) {cout << recv_buffer[j] << " ";}
  cout << " in rank = " << rank << endl;

  MPI_Scatter(&data_array, send_count, MPI_INT, &recv_buffer, recv_count, MPI_INT, 0, MPI_COMM_WORLD);

  cout << "After Scatter, data_array = ";
  for (int j=0; j<8; j++) {cout << data_array[j] << " ";}
  cout << " in rank = " << rank << endl;
  cout << "After Scatter, recv_buffer = ";
  for (int j=0; j<8; j++) {cout << recv_buffer[j] << " ";}
  cout << " in rank = " << rank << endl;

  MPI_Finalize();
  return 0;
}

