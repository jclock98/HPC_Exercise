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
        //get time
        gethostname(hostname, HOST_NAME_MAX + 1);
        for (int i = 0; i < HOST_NAME_MAX+1; i++){
            MPI_Send(&hostname[i], 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }
        
        for (int i = 0; i < HOST_NAME_MAX+1; i++){
            MPI_Recv(&hostname[i], 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("Received hostname in process %d: %s\n", my_rank, hostname);
        //display exec time
        
    } else if (my_rank == 1) {
            //get time
            for (int i = 0; i < HOST_NAME_MAX+1; i++){
                MPI_Recv(&hostname[i], 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            printf("Received hostname in process %d: %s\n", my_rank, hostname);

            gethostname(hostname, HOST_NAME_MAX + 1);
            
            for (int i = 0; i < HOST_NAME_MAX+1; i++){
                MPI_Send(&hostname[i], 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            }
            //display exec time
    }
    
    MPI_Finalize();
    return 0;
}