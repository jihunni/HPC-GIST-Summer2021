# include <iostream>
# include <cstdlib>
# include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
	// Get the rank and size in the original communicator
	int rank, nprocs;
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    // Split the communicator based on the color (global rank/4)
    // Your Code
	int color = rank / 4;
	MPI_Comm group_comm;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &group_comm);

    // get new rank and size
	int group_rank, group_nprocs;
	MPI_Comm_rank(group_comm, &group_rank);
	MPI_Comm_size(group_comm, &group_nprocs);

	printf("World_Rank/World_Nprocs: %d/%d \t Group_Rank/Group_Nprocs: %d/%d\n",
			rank, nprocs, group_rank, group_nprocs);

    // MPI Comm Free
	MPI_Comm_free(&group_comm);

    MPI_Finalize();
    return 0;
}
