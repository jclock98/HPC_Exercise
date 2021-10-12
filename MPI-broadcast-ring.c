#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void){

    double n_p;
    int comm_sz;
    int my_rank;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0){

        printf("Enter value\n");
        scanf("%lf ", &n_p);

        MPI_Send(&n_p, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&n_p, 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if(my_rank != comm_sz-1){
            MPI_Send(&n_p, 1, MPI_DOUBL, my_rank+1, 0, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return 0;
}