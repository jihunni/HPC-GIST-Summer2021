# include <iostream>
# include <cstdlib> // has exit(), etc.
# include <ctime>
# include <stdio.h>
# include "mpi.h"   // MPI header file

#define SIZE 4
#define MASTER 0
using namespace std;

int main (int argc, char **argv)
{
  int nprocs, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // the data to be distributed
  char data[SIZE][SIZE] = {
    {'a', 'b', 'c', 'd'},
    {'e', 'f', 'g', 'h'},
    {'i', 'j', 'k', 'l'},
    {'m', 'n', 'o', 'p'}
  };

  char recvbuf[100];
  int sendcounts[nprocs];
  int displs[nprocs];

  // calculate send counts and displacements
  for (int i = 0; i < nprocs; i++) {
    sendcounts[i] = i+1;
    displs[i] = i*SIZE;
  }

  // print calculated send counts and displacements for each process
  if (rank == 0) {
    for (int i = 0; i < nprocs; i++) {
      printf("sendcounts[%d] = %d\tdispls[%d] = %d\n", i, sendcounts[i], i, displs[i]);
    }
  }

  // MPI Scatterv
  MPI_Scatterv(&data, sendcounts, displs, MPI_CHAR, &recvbuf, SIZE, MPI_CHAR, MASTER, MPI_COMM_WORLD);

  printf("%d: ", rank);
  for (int i = 0; i < sendcounts[rank]; i++) {
    printf("%c\t", recvbuf[i]);
  }
  printf("\n");

  MPI_Finalize();
  return 0;
}

