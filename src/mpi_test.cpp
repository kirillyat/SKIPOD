#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv) {

    int numtasks, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("HELLO from #%d of %d",rank, numtasks);

    MPI_Finalize();
    return(0);
}