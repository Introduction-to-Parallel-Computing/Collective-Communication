#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

struct maxloc
{
    float value;
    int processor;
};

void Check_MPI_Routines (int return_value, char *mpi_routine);                                           // Δήλωση του πρωτότυπου της συνάρτησης "Check_MPI_Routines ()" που ο κώδικας της βρίσκεται στις γραμμές 192-199
void Check_Memory_Int (int *vec);
void Check_Memory_Float (float *vec); // Δήλωση του πρωτότυπου της συνάρτησης "Check_Memory ()" που ο κώδικας της βρίσκεται στις γραμμές 201-208
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
    /******************************************************************************************* Έναρξη του MPI περιβάλλοντος **************************************************************************************/   
    Check_MPI_Routines (MPI_Init (&argc, &argv), "MPI_Init ()");                                         // Έναρξη της χρήσης των MPI ρουτίνων και έλεγχος με την "Check_MPI_Routines ()" για τυχόν δυσλειτουργία
    Check_MPI_Routines (MPI_Comm_rank (MPI_COMM_WORLD, &rank), "MPI_Comm_rank ()");                       // Εκχώρηση στην rank το αναγνωριστικό της κάθε διεργασίας και έλεγχος με την "Check_MPI_Routines ()" για τυχόν δυσλειτουργία
    Check_MPI_Routines (MPI_Comm_size (MPI_COMM_WORLD, &p), "MPI_Comm_size ()");                          // Εκχώρηση στην p το πλήθος των διεργασιών και έλεγχος με την "Check_MPI_Routines ()" για τυχόν δυσλειτουργία
 /******************************************************************************************* Ατέρμονος βρόχος **************************************************************************************************/
    //while (1)                                                                                           
    //{
/*-------------------------------------------------------------------------------------------------- P0 --------------------------------------------------------------------------------------------------------*/
        root = 0;
        if (rank == root)                                                                                   /* Κώδικας που θα εκτελέσει μόνο η διεργασία P0 */
        {
            do                                                                                           /* Β΄ροχος για την εξασφάλιση ότι το μέγεθος της ακολουθίας θα είναι ακέραιο πολλαπλάσιο με το πλήθος των διεργασιών */
            {
                system ("clear");                                                                        // Καθαρισμός της οθόνης 
                printf ("Number of processors are %d\n", p);                                             // Εκτύπωση του πλήθους των διεργασιών 
                printf ("Size of integers' sequence must be integer multiple of number of processors (N mod processors == 0).\n"); // Εκτύπωση της συνθήκης του βρόχου σε φυσική γλώσσα
                printf ("Input the size of integers' sequence : ");                                      // Εκτύπωση για εισαγωγή του μεγέθους της ακολουθίας
                scanf ("%d", &N);                                                                        // Εισαγωγή του μεγέθους της ακολουθίας 
            }
            while (N % p != 0);                                                                          /* Η συνθήκη */
            
            X = (int *) malloc (N * sizeof (int));                                                     // Δυναμική δέσμευση μνήμης για την αποθήκευση της ακολουθίας
            Check_Memory_Int (X);                                                                          // Έλεγχος με την "Check_Memory ()" για τυχόν δυσλειτουργία
            printf ("Input elements of vector X\n");                                                   // Εκτύπωση για εισαγωγή στοιχείων στην ακολουθία
            for (i = 0; i < N; i++)                                                                      /* Βρόχος για την προσπέλαση της ακολουθίας */
            {
                printf ("X[%d] : ", i);                                                                // Εκτύπωση των θέσεων της ακολουθίας
                scanf ("%d", &X[i]);                                                                   // Εισαγωγή στοιχείων στην ακολουθίας
            }
            m = Count_Avg (X, N);
        }
        Check_MPI_Routines (MPI_Bcast (&N, 1, MPI_INT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        Check_MPI_Routines (MPI_Bcast (&m, 1, MPI_FLOAT, root, MPI_COMM_WORLD), "MPI_Bcast ()");
        elements_per_p = N / p;
        local_X = (int *) malloc (elements_per_p * sizeof (int));                                                     // Δυναμική δέσμευση μνήμης για την αποθήκευση της ακολουθίας
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

/****************************************************************************************** Κώδικας Check_MPI_Routines ******************************************************************************************/ 
void Check_MPI_Routines (int return_value, char *mpi_routine)                                            /* Η συνάρτηση ελέγχου των τιμών επιστροφής των MPI ρουτίνων για τυχόν σφάλματα */
{
    if (return_value != MPI_SUCCESS)                                                                     /* Η τιμή επιστροφής της MPI ρουτίνας είναι σφάλματος */
    {
        printf ("Error in executing MPI routine \"%s\"\n", mpi_routine);                                 // Εκτύπωση μηνύματος σφάλματος κατά την εκτέλεση μίας MPI ρουτίνας
        MPI_Abort (MPI_COMM_WORLD, return_value);                                                        // Εγκατάλειψη της χρήσης των MPI ρουτίνων
    }
}
/****************************************************************************************** Κώδικας Check_Memory *************************************************************************************************/ 
void Check_Memory_Int (int *vec)                                                                             /* Η συνάρτηση ελέγχου της δυναμικής δέσμευσης πινάκων για τυχόν σφάλματα */
{
    if (!vec)                                                                                            /* Αδυναμία δέσμευσης μνήμης */
    {
        printf ("Error in allocating heap memory\n");                                                    // Εκτύπωση μηνύματος σφάλματος κατά την δυναμική δέσμευση
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Τερματισμός του προγράμματος με τιμή επιστροφής 1
    }
}

void Check_Memory_Float (float *vec)                                                                             /* Η συνάρτηση ελέγχου της δυναμικής δέσμευσης πινάκων για τυχόν σφάλματα */
{
    if (!vec)                                                                                            /* Αδυναμία δέσμευσης μνήμης */
    {
        printf ("Error in allocating heap memory\n");                                                    // Εκτύπωση μηνύματος σφάλματος κατά την δυναμική δέσμευση
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Τερματισμός του προγράμματος με τιμή επιστροφής 1
    }
}

void Check_Memory_Struct (struct maxloc *vec)                                                                             /* Η συνάρτηση ελέγχου της δυναμικής δέσμευσης πινάκων για τυχόν σφάλματα */
{
    if (!vec)                                                                                            /* Αδυναμία δέσμευσης μνήμης */
    {
        printf ("Error in allocating heap memory\n");                                                    // Εκτύπωση μηνύματος σφάλματος κατά την δυναμική δέσμευση
        Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()"); 
        exit (1);                                                                                        // Τερματισμός του προγράμματος με τιμή επιστροφής 1
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