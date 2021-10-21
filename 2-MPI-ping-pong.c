#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>

const int MAX_STRING = 100;

int main(void){

    double n_p;
    int comm_sz;
    int my_rank;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0){

        // get time
        // get hostname
        MPI_Send(&n_p, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&n_p, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //display exec time
        
    } else {
        // get time
        MPI_Recv(&n_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // get hostname
        MPI_Send(&n_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        // display exec time
    }
    
    MPI_Finalize();
    return 0;
}