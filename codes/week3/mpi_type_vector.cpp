#include <iostream>
#include <mpi.h>		// MPI header file
#define MASTER 0
#define WORKER 1

/**
 * @brief Illustrates how to create a vector MPI datatype.
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver. These two MPI processes will exchange a message made of three
 * integers. On the sender, that message is in fact the middle column of an
 * array it holds, which will be represented by an MPI vector.
 *
 *
 *     Full array          What we want
 *                            to send
 * +-----+-----+-----+  +-----+-----+-----+
 * |  0  |  1  |  2  |  |  -  |  1  |  -  |
 * +-----+-----+-----+  +-----+-----+-----+
 * |  3  |  4  |  5  |  |  -  |  4  |  -  |
 * +-----+-----+-----+  +-----+-----+-----+
 * |  6  |  7  |  8  |  |  -  |  7  |  -  |
 * +-----+-----+-----+  +-----+-----+-----+
 *
 * How to extract a column with a vector type:
 *
 *                 distance between the
 *            start of each block: 3 elements
 *          <---------------> <--------------->
 *         |                 |                 |
 *      start of          start of          start of
 *      block 1           block 2           block 3
 *         |                 |                 |
 *         V                 V                 V
 *   +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *   |  -  |  1  |  -  |  -  |  4  |  -  |  -  |  7  |  -  |
 *   +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *          <--->             <--->             <--->
 *         block 1           block 2           block 3
 * 
 * Block length: 1 element
 * Element: MPI_INT
 **/

using namespace std;

int main(int argc, char **argv) {
  int nprocs, rank;

  // initialize for MPI
  MPI_Init(&argc, &argv);
  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
  // get the rank = this process's number (ranges from 0 to nprocs - 1)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // master send value to workers
  if (rank == MASTER) 
  {
    // Create the datatype
    MPI_Datatype column_type;
    MPI_Type_vector(3, 1, 3, MPI_INT, &column_type);
    MPI_Type_commit(&column_type);
 
    // send the message
    int buffer[3][3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    MPI_Request request;
    cout << "MPI process " << rank << " sends values " 
         << buffer[0][1] << ", " << buffer[1][1] 
         << ", and " << buffer[2][1] << endl;
    MPI_Send(&buffer[0][1], 1, column_type, WORKER, 0, MPI_COMM_WORLD);
  }

  // workers receive the message
  if (rank == WORKER) 
  {
    int received[3];
    MPI_Recv(&received, 3, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout << "MPI process " << rank << " received values " 
         << received[0] << ", " << received[1]
         << ", and " << received[2] << endl;
  }
    
  // clean up for MPI
  MPI_Finalize();   // C style

  return 0;
}

