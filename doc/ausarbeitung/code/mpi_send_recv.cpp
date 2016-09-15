MPI_Send(void *data, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm);
MPI_Recv(void *data, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm,MPI_Status *status);
