#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>

const int HOST_NAME_MAX = 1024;

int main(void){

    char hostname[HOST_NAME_MAX + 1];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0){

        // get hostname

        gethostname(hostname, HOST_NAME_MAX + 1);
        
        printf("[PROCESS %d] Sending hostname %s from process %d to process %d!\n", my_rank, hostname, my_rank, my_rank+1);
        
        MPI_Send(&hostname, HOST_NAME_MAX+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        
    } else {
        
        MPI_Recv(&hostname, HOST_NAME_MAX+1, MPI_CHAR, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        

        printf("[PROCESS %d] Received hostname %s from process %d!\n", my_rank, hostname, my_rank-1);

        if(my_rank != comm_sz-1){
            printf("[PROCESS %d] Sending hostname %s from process %d to process %d!\n", my_rank, hostname, my_rank, my_rank+1);
            
            MPI_Send(&hostname, HOST_NAME_MAX+1, MPI_CHAR, my_rank+1, 0, MPI_COMM_WORLD);
            
        }
    }
    
    MPI_Finalize();
    return 0;
}