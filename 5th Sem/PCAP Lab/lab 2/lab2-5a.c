//Implement at least 2 programs to identify deadlock conditions in synchronous send and
//standard send with multiple point to point communications between two processes

#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    int rank, x=1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(rank==0)
    {
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Number recv: %d", x);
    }
    MPI_Finalize();
}