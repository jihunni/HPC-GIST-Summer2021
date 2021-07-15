# include <iostream>
# include <cstdlib>	// has exit(), etc.
# include <ctime>
# include "mpi.h"	// MPI header file

using namespace std;

//****************************************************************************80
int main (int argc, char **argv)
//****************************************************************************80
{
  int data_array[8] = {};
  int recv_buffer[8] = {};
  int nprocs, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // assign data_array
  for (int i=0; i<2; i++) {
    data_array[i] = 100+i+rank*2;
  }
  // at rank=0, data_array[0]=100, data_array[1]=101
  // at rank=1, data_array[0]=102, data_array[1]=103 
  // at rank=2, data_array[0]=104, data_array[1]=105 
  // at rank=3, data_array[0]=106, data_array[1]=107 

  int send_count = 2;
  int recv_count = 2;

  cout << "Before Gather, data_array = ";
  for (int j=0; j<8; j++) {cout << data_array[j] << " ";}
  cout << " in rank = " << rank << endl;
  cout << "Before Gather, recv_buffer = ";
  for (int j=0; j<8; j++) {cout << recv_buffer[j] << " ";}
  cout << " in rank = " << rank << endl;

  MPI_Gather(&data_array, send_count, MPI_INT, &recv_buffer, recv_count, MPI_INT, 0, MPI_COMM_WORLD);

  cout << "After Gather, data_array = ";
  for (int j=0; j<8; j++) {cout << data_array[j] << " ";}
  cout << " in rank = " << rank << endl;
  cout << "After Gather, recv_buffer = ";
  for (int j=0; j<8; j++) {cout << recv_buffer[j] << " ";}
  cout << " in rank = " << rank << endl;

  // get average
  if (rank == 0) {
    float avg = 0;
    float sum = 0;
    for (int i=0; i<8; i++) {
      sum += recv_buffer[i];
    }
    avg = sum / 8;
    cout << "Avg = " << avg << endl;
  }

  MPI_Finalize();
  return 0;
}

