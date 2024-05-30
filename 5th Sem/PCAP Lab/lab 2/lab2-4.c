//Write a MPI program to read an integer value in the root process. Root process sends this
//value to Process1, Process1 sends this value to Process2 and so on. Last process sends the
//value back to root process. When sending the value each process will first increment the
//received value by one. Write the program using point to point communication routines.

#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if(rank==0)
    {
        printf("Enter a number: ");
        fflush(stdout);
        scanf("%d", &x);
        x++;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        printf("Finally: %d\n", x);
    }
    else if(rank!=size-1)
    {
        MPI_Recv(&x, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printf("Rank %d|No recv %d\n", rank, x);
        // fflush(stdout);
        x++;
        MPI_Send(&x, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printf("Rank %d|No rec: %d\n", rank, x);
        fflush(stdout);
        x++;
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}