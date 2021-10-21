#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>

/*
Run on cluster using
~ 1 process - 1 core
~ 2 processes - 1 core
~ 2 processes - 2 cores, 1 node
~ 16 processes - 4, 8, 16 cores, 1 node
~ 2 processes - 2 cores, 2 nodes
*/

const int HOST_NAME_MAX = 1024;

int main(void){
    int comm_sz;
    int my_rank;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char hostname[HOST_NAME_MAX + 1];
    
    gethostname(hostname, HOST_NAME_MAX + 1);
    printf("Greetings %s!\n",
                hostname);

    MPI_Finalize();
    return 0;
}