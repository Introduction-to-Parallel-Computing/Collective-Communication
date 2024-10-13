struct maxloc
{
    float value;
    int processor;
};

void Check_MPI_Routines (int return_value, char *mpi_routine);                                           // Declaration of the prototype for the "Check_MPI_Routines ()" function, whose code is located in lines 192-199
void Check_Memory_Int (int *vec);
void Check_Memory_Float (float *vec); // Declaration of the prototype for the "Check_Memory ()" function, whose code is located in lines 201-208
void Check_Memory_Struct (struct maxloc *vec);
float Count_Avg (int *vec, int N);

int main (int argc, char *argv[])
{
    int rank, p, N, root, bcast_N, index;
    int *X;
    float *local_D, *D, *max_loc_val;
    int xmin, xmax;
    float m, bcast_m, local_var, global_var;
    int elements_per_p;
    int *local_X;
    int local_greater_than_m, local_less_than_m;
    int global_greater_than_m, global_less_than_m;
    int i;
    struct maxloc send, recv;

    /******************************************************************************************* Start of MPI environment **************************************************************************************/   
    Check_MPI_Routines (MPI_Init (&argc, &argv), "MPI_Init ()");                                         // Start of using MPI routines and check with "Check_MPI_Routines ()" for any malfunction
    Check_MPI_Routines (MPI_Comm_rank (MPI_COMM_WORLD, &rank), "MPI_Comm_rank ()");                       // Assign the rank the identifier of each process and check with "Check_MPI_Routines ()" for any malfunction
    Check_MPI_Routines (MPI_Comm_size (MPI_COMM_WORLD, &p), "MPI_Comm_size ()");                          // Assign to p the number of processes and check with "Check_MPI_Routines ()" for any malfunction

    /******************************************************************************************* Infinite Loop **************************************************************************************************/
    //while (1)                                                                                           
    //{
/*-------------------------------------------------------------------------------------------------- P0 --------------------------------------------------------------------------------------------------------*/
        root = 0;
        if (rank == root)                                                                                   /* Code that will be executed only by process P0 */
        {
            do                                                                                           /* Loop to ensure that the size of the sequence will be an integer multiple of the number of processes */
            {
                system ("clear");                                                                        // Clear the screen 
                printf ("Number of processors are %d\n", p);                                             // Print the number of processes 
                printf ("Size of integers' sequence must be integer multiple of number of processors (N mod processors == 0).\n"); // Print the loop condition in natural language
                printf ("Input the size of integers' sequence : ");                                      // Print for inputting the size of the sequence
                scanf ("%d", &N);                                                                        // Input the size of the sequence 
            }
            while (N % p != 0);                                                                          /* The condition */
            
            X = (int *) malloc (N * sizeof (int));                                                     // Dynamic memory allocation for storing the sequence
            Check_Memory_Int (X);                                                                          // Check with "Check_Memory ()" for any malfunction
            printf ("Input elements of vector X\n");                                                   // Print for inputting elements into the sequence
            for (i = 0; i < N; i++)                                                                      /* Loop for accessing the sequence */
            {
                printf ("X[%d] : ", i);                                                                // Print the positions of the sequence
                scanf ("%d", &X[i]);                                                                   // Input elements into the sequence
            }
            m = Count_Avg (X, N);
        }
        Check_MPI_Routines (MPI_Bcast (&N, 1, MPI_INT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        Check_MPI_Routines (MPI_Bcast (&m, 1, MPI_FLOAT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        elements_per_p = N / p;
        local_X = (int *) malloc (elements_per_p * sizeof (int));                                                     // Dynamic memory allocation for storing the sequence
        Check_Memory_Int (local_X);
        Check_MPI_Routines (MPI_Scatter (X, elements_per_p, MPI_INT, local_X, elements_per_p, MPI_INT, root, MPI_COMM_WORLD), "MPI_Scatter ()");
        //for (i = 0; i < elements_per_p; i++)
          //  printf ("rank = %d, local[%d] = %f\n", rank, i, local_X[i]);
        local_greater_than_m = 0;
        local_less_than_m = 0;
        for (i = 0; i < elements_per_p; i++)
        {
            if (local_X[i] > m)
                local_greater_than_m++;
            else
                if (local_X[i] < m)
                   local_less_than_m++;
        }
        Check_MPI_Routines (MPI_Reduce (&local_greater_than_m, &global_greater_than_m, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD), "MPI_Reduce ()");
        Check_MPI_Routines (MPI_Reduce (&local_less_than_m, &global_less_than_m, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD), "MPI_Reduce ()");
        if (rank == root)
        {
            printf ("---------------------------------------\n");
            printf ("Question A\n");
            printf ("Number of elements that are greater than average %f : %d\n", m, global_greater_than_m);
            printf ("Number of elements that are less than average %f    : %d\n", m, global_less_than_m);
        }
        for (i = 0; i < elements_per_p; i++)
            local_var += (local_X[i] - m) * (local_X[i] - m);
        local_var /= N;
        root = 0;
        Check_MPI_Routines (MPI_Reduce (&local_var, &global_var, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD), "MPI_Reduce ()");
        if (rank == root)
        {
            printf ("---------------------------------------\n");
            printf ("Question B\n");
            printf ("var = ((X0 - m)^2 + (X1 - m)^2 + ... + (Xn-1 - m)^2) / n\n");
            printf ("var : %f\n", global_var);  
        }
        root = 0;
        Check_MPI_Routines (MPI_Reduce (local_X, &xmin, 1, MPI_INT, MPI_MIN, root, MPI_COMM_WORLD), "MPI_Reduce ()");
        Check_MPI_Routines (MPI_Reduce (local_X, &xmax, 1, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD), "MPI_Reduce ()");
        Check_MPI_Routines (MPI_Bcast (&xmin, 1, MPI_INT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        Check_MPI_Routines (MPI_Bcast (&xmax, 1, MPI_INT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        local_D = (float *) malloc (elements_per_p * sizeof(float));
        Check_Memory_Float (local_D);
        for (i = 0; i < elements_per_p; i++)
            local_D[i] = ((float)(local_X[i] - xmin) / (xmax - xmin)) * 100.0;
        D = (float *) malloc (elements_per_p * sizeof(float));
        Check_Memory_Float (D);
        root = 0;
        Check_MPI_Routines (MPI_Gather (local_D, elements_per_p, MPI_INT, D, elements_per_p, MPI_INT, root, MPI_COMM_WORLD), "MPI_Gather ()");
        if (rank == root)
        {
            printf ("---------------------------------------\n");
            printf ("Question C\n");
            printf ("Di = ((Xi - Xmin) / (Xmax - Xmin)) * 100\n");
            for (i = 0; i < N; i++)
                printf ("D[%d] : %f\n", i, D[i]);
        }
        send.value = local_D[0];
        send.processor = 0;
        for (i = 0; i < elements_per_p; i++)
        {
            if (local_D[i] > send.value)
            {
                send.value = local_D[i];
                send.processor = i;
            }
        }
        root = 0;
Check_MPI_Routines (MPI_Reduce (&send, &recv, 1, MPI_FLOAT_INT, MPI_MAXLOC, root, MPI_COMM_WORLD), "MPI_Reduce ()");
if (rank == root)
{
  //  for (i = 0; i < N; i++)
    //    if (X[i] == recv[0].value)
             //       index = i;
    printf ("---------------------------------------\n");
    printf ("Question D\n");
    printf ("Element's index of vector X with the highest D[i] : %d\n", recv.processor);
    printf ("Vector X's element with the highest D[i]          : %d\n", X[recv.processor]);
    printf ("Max D[i]                                          : %f\n", recv.value);
}
free (X);
free (D);
free (local_X);
free (local_D);
       
return 0;
}

/****************************************************************************************** Code for Check_MPI_Routines ******************************************************************************************/ 
void Check_MPI_Routines (int return_value, char *mpi_routine)                                            /* The function checks the return values of MPI routines for any errors */
{
    if (return_value != MPI_SUCCESS)                                                                     /* The return value of the MPI routine indicates an error */
    {
        printf ("Error in executing MPI routine \"%s\"\n", mpi_routine);                                 // Print an error message during the execution of an MPI routine
        MPI_Abort (MPI_COMM_WORLD, return_value);                                                        // Abort the use of MPI routines
    }
}

/****************************************************************************************** Code for Check_Memory *************************************************************************************************/ 
void Check_Memory_Int (int *vec)                                                                             /* The function checks dynamic memory allocation for arrays for any errors */
{
    if (!vec)                                                                                            /* Memory allocation failure */
    {
        printf ("Error in allocating heap memory\n");                                                    // Print an error message during dynamic allocation
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Terminate the program with return value 1
    }
}

void Check_Memory_Float (float *vec)                                                                             /* The function checks dynamic memory allocation for arrays for any errors */
{
    if (!vec)                                                                                            /* Memory allocation failure */
    {
        printf ("Error in allocating heap memory\n");                                                    // Print an error message during dynamic allocation
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Terminate the program with return value 1
    }
}

void Check_Memory_Struct (struct maxloc *vec)                                                                             /* The function checks dynamic memory allocation for arrays for any errors */
{
    if (!vec)                                                                                            /* Memory allocation failure */
    {
        printf ("Error in allocating heap memory\n");                                                    // Print an error message during dynamic allocation
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Terminate the program with return value 1
    }
}

float Count_Avg (int *vec, int N)
{
    int i;
    float sum, avg;
    sum = 0;
    for (i = 0; i < N; i++)
        sum += vec[i];
    avg = sum / N;
        
    return avg;
}
