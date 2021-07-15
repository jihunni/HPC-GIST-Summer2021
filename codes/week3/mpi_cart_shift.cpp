# include <iostream>
# include <cstdlib>
# include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{
    // MPI Init and get rank
    int rank, nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	// Variables required by Create_cart
	int ndims, dims[2], periods[2], reorder;
	ndims = 2;		    // 2D matrix/grid
	dims[0] = 3;		// rows
	dims[1] = 4;		// columns
	periods[0] = true;	// row periodic (each column forms a ring)
	periods[1] = true;	// columns periodic (each row forms a ring)
	reorder = true;		// allows processes reordered for efficiency

	// Create a communicator given the 2D torus topology.
	MPI_Comm new_comm;
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &new_comm);

    // Torus rank in the new communicator
    int torus_rank;
    MPI_Comm_rank(new_comm, &torus_rank);

    // Get my coordinates in the new communicator
    int torus_coords[2];
    MPI_Cart_coords(new_comm, torus_rank, ndims, torus_coords);

    // Print my location in the 2D torus
    cout << "rank:" << rank
         << "> torus_rank=" << torus_rank
         << ", coords=(" << torus_coords[0] << "," << torus_coords[1] << ")" << endl;

    // Declare our neighbours
    enum DIRECTIONS {DOWN, UP, LEFT, RIGHT};
    const char* neighbours_names[4] = {"DOWN", "UP", "LEFT", "RIGHT"};
    int neighbours_ranks[4];

    // Let consider dims[0] = X, so the shift tells us our left and right neighbours
    MPI_Cart_shift(new_comm, 0, 1, &neighbours_ranks[UP], &neighbours_ranks[DOWN]);
    MPI_Cart_shift(new_comm, 1, 1, &neighbours_ranks[LEFT], &neighbours_ranks[RIGHT]);

    // Get my rank
	int my_rank;
    MPI_Comm_rank(new_comm, &my_rank);

	// Print my neighbors
	for(int i = 0; i < 4; i++)
    {
       cout << "MPI rank=" << my_rank << " I have a " << neighbours_names[i]
            << " neighbour rank=" << neighbours_ranks[i] << endl;
    }

	// MPI finalize and exit
	MPI_Finalize();
	return 0;
}

