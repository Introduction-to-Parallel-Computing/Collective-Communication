![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Flag_of_the_United_Kingdom_%281-2%29.svg/255px-Flag_of_the_United_Kingdom_%281-2%29.svg.png)

# MPI Program for Vector Analysis with Collective Communication

For the requested Assignment, click the link:
[Assignment](Assignment/)

For the Source Code, click the link:
[Code](Code/)

For the detailed Documentation, click the link:
[Documentation](Documentation/)

## Overview

This project implements an MPI (Message Passing Interface) program in C to analyze a vector \(X\) (of length \(n\)). The program computes various statistics about the vector in a parallel environment with \(p\) processors, including the mean, minimum, and maximum values, and derives additional properties such as dispersion, percentage relationships, and prefix sums.

## Objectives

The program fulfills the following tasks:

1. **Count Elements Relative to Mean**: Determine how many elements of the vector \(X\) are less than and greater than the mean \(m\).
2. **Calculate Dispersion**: Compute the variance of the elements of vector \(X\).
3. **Percentage Vector**: Create a new vector \(D\) where each element \(y_i\) represents the percentage relationship of the corresponding element \(x_i\) of vector \(X\) relative to the difference between the maximum and minimum values.
4. **Max Value in Vector \(D\)**: Identify the largest value in vector \(D\), along with its corresponding element \(x_i\) in vector \(X\) and the index of the element.
5. **Prefix Sums**: Calculate the prefix sums of the elements of vector \(X\).

## Course Information

- **Course**: [Introduction to Parallel Computing](https://ice.uniwa.gr/education/undergraduate/courses/introduction-to-parallel-computing/)
- **Semester**: 5
- **Program of Study**: [UNIWA](https://www.uniwa.gr/)
- **Department**: [Informatics and Computer Engineering](https://ice.uniwa.gr/)
- **Lab Instructor**: [Iordanakis Michael](https://ice.uniwa.gr/academic_sc_ho/)
- **Academic Season**: 2022-2023

## Student Information

- **Name**: Athanasiou Vasileios Evangelos
- **Student ID**: 19390005
- **Status**: Undergraduate

## Program Structure

### Main MPI Program

- **File**: `collective_communication.c`
- **Functionality**: 
  - Reads the vector size \(N\) and its elements from the user.
  - Distributes the workload among \(p\) processors for parallel computations.
  - Collects results from all processors and prints the analysis, including the prefix sum.

### Menu and Iteration

- The program provides a user-friendly menu with options to:
  1. Continue analyzing another vector.
  2. Exit the program.
- The menu is displayed iteratively until the user chooses to exit.

## Requirements

- **Operating System**: Linux-based OS or any Unix-like system that supports MPI.
- **Compiler**: GCC (GNU Compiler Collection).
- **Libraries**: MPI library (`mpi.h`).

## Installation and Usage

### 1. Clone the Repository
Download the repository to your local machine:
```
git clone https://github.com/Introduction-to-Parallel-Computing/Collective-Communication.git
```
### 2. Compile the Source Code
Compile the MPI program using the GCC compiler:
```
mpicc -o collective_communication collective_communication.c
```
### 3. Run the Program
Run the MPI program using the `mpirun` or `mpiexec` command, specifying the number of processes:
```
mpirun -np <number_of_processors> ./collective_communication
```

![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Flag_of_Greece.svg/255px-Flag_of_Greece.svg.png)

# MPI Πρόγραμμα Ανάλυσης Διανύσματος με Συλλογική Επικοινωνία

Για την ζητούμενη Άσκηση, κάντε κλικ στον σύνδεσμο:
[Άσκηση](Assignment/)

Για τον Πηγαίο Κώδικα, κάντε κλικ στον σύνδεσμο:
[Κώδικας](Code/)

Για την Αναλυτική Τεκμηρίωση, κάντε κλικ στον σύνδεσμο:
[Τεκμηρίωση](Documentation/)

## Επισκόπηση

Αυτό το έργο υλοποιεί ένα πρόγραμμα MPI (Message Passing Interface) σε γλώσσα C για την ανάλυση ενός διανύσματος \(X\) (μήκους \(n\)). Το πρόγραμμα υπολογίζει διάφορες στατιστικές σχετικά με το διάνυσμα σε ένα παράλληλο περιβάλλον με \(p\) επεξεργαστές, περιλαμβάνοντας τον μέσο, τον ελάχιστο και τον μέγιστο αριθμό, και εξάγει επιπλέον ιδιότητες όπως διασπορά, ποσοστιαίες σχέσεις και πρόθετα αθροίσματα.

## Στόχοι

Το πρόγραμμα εκπληρώνει τις εξής εργασίες:

1. **Μέτρηση Στοιχείων Σχετικά με τον Μέσο**: Να προσδιορίσει πόσα στοιχεία του διανύσματος \(X\) είναι μικρότερα και πόσα μεγαλύτερα από τον μέσο \(m\).
2. **Υπολογισμός Διασποράς**: Να υπολογίσει την διακύμανση των στοιχείων του διανύσματος \(X\).
3. **Ποσοστό Διανύσματος**: Να δημιουργήσει ένα νέο διάνυσμα \(D\) όπου κάθε στοιχείο \(y_i\) αντιπροσωπεύει τη ποσοστιαία σχέση του αντίστοιχου στοιχείου \(x_i\) του διανύσματος \(X\) σχετικά με την διαφορά μεταξύ των μέγιστων και ελάχιστων τιμών.
4. **Μέγιστη Τιμή στο Διάνυσμα \(D\)**: Να προσδιορίσει την μεγαλύτερη τιμή στο διάνυσμα \(D\), μαζί με το αντίστοιχο στοιχείο \(x_i\) στο διάνυσμα \(X\) και τον δείκτη του στοιχείου.
5. **Πρόθετα Αθροίσματα**: Να υπολογίσει τα πρόθετα αθροίσματα των στοιχείων του διανύσματος \(X\).

## Πληροφορίες Μαθήματος

- **Μάθημα**: [Εισαγωγή στον Παράλληλο Υπολογισμό](https://ice.uniwa.gr/education/undergraduate/courses/introduction-to-parallel-computing/)
- **Εξάμηνο**: 5
- **Πρόγραμμα Σπουδών**: [ΠΑΔA](https://www.uniwa.gr/)
- **Τμήμα**: [Πληροφορική και Μηχανική Υπολογιστών](https://ice.uniwa.gr/)
- **Διδάσκων**: [Ιορδανάκης Μιχαήλ](https://ice.uniwa.gr/academic_sc_ho/)
- **Ακαδημαϊκή Χρονιά**: 2022-2023

## Πληροφορίες Φοιτητή

- **Όνομα**: Αθανασίου Βασίλειος Ευάγγελος
- **ΑΜ**: 19390005
- **Κατάσταση**: Προπτυχιακός

## Δομή Προγράμματος

### Κύριο Πρόγραμμα MPI

- **Αρχείο**: `collective_communication.c`
- **Λειτουργικότητα**: 
  - Διαβάζει το μέγεθος του διανύσματος \(N\) και τα στοιχεία του από τον χρήστη.
  - Κατανέμει το φόρτο εργασίας μεταξύ \(p\) επεξεργαστών για παράλληλους υπολογισμούς.
  - Συγκεντρώνει τα αποτελέσματα από όλους τους επεξεργαστές και εκτυπώνει την ανάλυση, συμπεριλαμβανομένου του πρόθετου αθροίσματος.

### Μενού και Επανάληψη

- Το πρόγραμμα παρέχει ένα φιλικό προς τον χρήστη μενού με επιλογές για:
  1. Συνέχιση της ανάλυσης ενός άλλου διανύσματος.
  2. Έξοδο από το πρόγραμμα.
- Το μενού εμφανίζεται επαναληπτικά μέχρι ο χρήστης να επιλέξει να εξοφλήσει.

## Απαιτήσεις

- **Λειτουργικό Σύστημα**: Linux-based OS ή οποιοδήποτε Unix-like σύστημα που υποστηρίζει MPI.
- **Μεταγλωττιστής**: GCC (GNU Compiler Collection).
- **Βιβλιοθήκες**: Βιβλιοθήκη MPI (`mpi.h`).

## Εγκατάσταση και Χρήση

### 1. Κλωνοποιήστε το αποθετήριο
Κατεβάστε το αποθετήριο στον τοπικό σας υπολογιστή:
```
git clone https://github.com/Introduction-to-Parallel-Computing/Collective-Communication.git
```
### 2. Μεταγλωττίστε τον Πηγαίο Κώδικα
Συμπιέστε το πρόγραμμα MPI χρησιμοποιώντας τον μεταγλωττιστή GCC:
```
mpicc -o collective_communication collective_communication.c
```
### 3. Εκτέλεση του Προγράμματος
Εκτελέστε το πρόγραμμα MPI χρησιμοποιώντας την εντολή `mpirun` ή `mpiexec`, καθορίζοντας τον αριθμό των διεργασιών:
```
mpirun -np <number_of_processors> ./collective_communication
```
