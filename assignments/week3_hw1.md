---
layout: default
title: week3 hw1
nav_exclude: true
---
## Homework Assignment
week3 hw1

## Score
100

## Due
Wed, Jul-21-2021, 11:59 PM 

## Problem 1
Calculate Pi using the Monte-carlo method and MPI. Read the slide of Week 3 second lecture (HPC_Lec07_MPI_P2P.pdf). Run the program with n=10,000,000 and n= 100,000,000 cases using P=1, 2, 4, 8, 16. Check the PI calculation precision having ~= 3.141. Plot x-axis = P (log-scale preferred) and y-axis = wall-clock time. Finally, analyze the wall-clock time and speed-up with your words for two cases.

```
#include <iostream>
#include <iomanip>
#include <mpi.h>
#define MASTER 0
#define SEED 35791246

using namespace std;

int main(int argc, char **argv)
{
    int nprocs, rank, npoints, circle_count=0, num, val;
    double x, y, pi, stime, etime;

    // MPI Init and rank
    // Your code

    if (rank == MASTER)
        stime = MPI_Wtime(); // start time

    // Get number of points
    npoints = 10000000;
    if (argc >= 2)
        npoints = atoi(argv[1]);

    // Calculate number of points for each rank
    // Your code
    // You should consider npoints is not divided nprocs

    // Random numbers and count the points of inside of the circle
    srand(SEED+rank);   // Give rand() a seed value
    // Your code

    if (rank == MASTER) // I am MASTER
    {
        // Your code
        etime = MPI_Wtime(); // end time
        cout << "  " << setw(10) << "npoints"
             << "  " << setw(10) << "pi"
             << "  " << setw(10) << "nprocs"
             << "  " << setw(30) << "elapsed wall-clock time" << "\n";
        cout << "  " << setw(10) << npoints
             << "  " << setw(10) << pi
             << "  " << setw(10) << nprocs
             << "  " << setw(30) << etime-stime << "\n";
    }
    else  // I am WORKER
    {
        // Your code
    }

    // MPI finalize
    MPI_Finalize();
}
```
If the n size is small to achieve an enough speedup, you can increase n as you want.


## Problem 2

Complete the Matrix-Vector multiplication (row-wise).

Assuming: Set N(4) X M(4) matrix and M(4)X1 vector using 4 processors. Please use M and N variables to iterate matrix/vector initialization and mathematical computation.

Be careful: Initialize the A matrix and B vector at MASTER!

```
#include <iostream>
#include <cstdlib>     // has exit(), etc.
#include <ctime>
#include <mpi.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
  // Just simply set N(4) X M(4) matrix and M(4) X 1 vector
  int N=4, M=4;
  int A[N][M], Apart[M], B[M], X[N];
  int Xpart = 0, root=0;
  int nproc, rank;

  // MPI init
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Initialize matrix
  if (rank == MASTER) {

    ...

  }

  // MPI Scatter the A Matrix

  ...

  // Broadcast the B vector

  ...

  // Calculate Xpart

  ...

  // MPI Gather

  ...

  // Print results

  if (rank == MASTER) {
    for(int i=0; i<N; i++) {
      cout << "X[" << i << "]=" << X[i] << endl;
  } }   

  MPI_Finalize();  // MPI finalize

  return 0;     // Exit

}
```

## Problem 3
Complete the Matrix-Vector multiplication using column-wise approach with same environment and assumption of Problem 2.


## Submit
- Submit a zip file including source codes and document (PDF) by email to taehyuk.ahn@gist.ac.kr
- Filename should be "HPC_week3_hw1_YourLastname_YourFirstName.gz"
- Email title should be "HPC week3 hw1 submission"
