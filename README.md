<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<hr/>

<p align="center">
  <strong>Introduction to Parallel Computing</strong>
</p>

<h1 align="center" style="letter-spacing: 1px;">
  Collective Communication
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<hr/>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Vasileios Mamalis, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/vassilios-mamalis/" target="_blank">UNIWA Profile</a>
</p>

<p align="center">
  Supervisor: Grammati Pantziou, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/grammati-pantziou/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/grammati-pantziou-4731bb10a/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Co-supervisor: Michalis Iordanakis, Special Technical Laboratory Staff
</p>

<p align="center">
  <a href="https://scholar.google.com/citations?user=LiVuwVEAAAAJ&hl=en" target="_blank">UNIWA Profile</a>
</p>

<hr/>

<p align="center">
  Athens, January 2023
</p>

---

# Project Overview

The primary objective of this exercise is to manage and process a vector **X** of size **N** across **p processes** using MPI and collective communication.


---

## Table of Contents

| Section | Folder | Description |
|------:|--------|-------------|
| 1 | `assign/` | Assignment material for the Collective Communication laboratory |
| 1.1 | `assign/PAR-LAB-EXER-II-2022-23.pdf` | Laboratory exercise description in English |
| 1.2 | `assign/ΠΑΡ-ΕΡΓ-ΑΣΚ-ΙΙ-2022-23.pdf` | Περιγραφή εργαστηριακής άσκησης (Greek) |
| 2 | `docs/` | Documentation and theoretical background on collective communication |
| 2.1 | `docs/Collective-Communication.pdf` | Theory and mechanisms of collective communication (EN) |
| 2.2 | `docs/Συλλογική-Επικοινωνία.pdf` | Θεωρία Συλλογικής Επικοινωνίας (EL) |
| 3 | `src/` | Source code implementing collective communication operations |
| 3.1 | `src/collective_communication.c` | C implementation of MPI collective communication primitives |
| 4 | `README.md` | Repository overview, build, and execution instructions |

---

### Architecture

The system follows a **manager–worker model**:

- **Process P₀ (Manager):**
  - Initializes and owns the full vector
  - Distributes vector segments to all processes (including itself)
  - Coordinates global calculations and gathers results

- **Worker Processes (P₁ … Pₚ₋₁):**
  - Perform computations on their assigned sub-vectors
  - Participate in collective communication operations

All calculations are executed **locally first** and then combined using **MPI collective routines**.

---

## Features & Calculations

The program performs the following operations on the distributed vector **X**:

### Question A - Comparison with Average
- Computes the **mean value** of the vector
- Counts:
  - Elements **greater than** the average
  - Elements **less than** the average

---

### Question B - Dispersion (Variance)

The dispersion (variance) is calculated using:

$$
\text{var} = \frac{\sum_{i=0}^{n-1} (X_i - m)^2}{n}
$$

where:

$$
m 
$$ 

is the mean value of the vector

---

### Question C - Percentage Relationship Vector

Computes a normalized percentage vector 

$$ 
D_i 
$$

:

$$
D_i = \frac{X_i - X_{min}}{X_{max} - X_{min}} \times 100
$$

This expresses each element’s relative position between the minimum and maximum values.

---

### Question D - Maximum Value and Index
- Identifies the **maximum value** in the vector
- Determines its **global index**

---

### Question E - Prefix Sum (Scan)
- Computes the **prefix sum vector** of **X**
- Each element contains the sum of all previous elements up to that position

---

## Repository Setup

```bash
git clone https://github.com/Introduction-to-Parallel-Computing/Collective-Communication.git
cd Collective-Communication/src
```

---

## Technical Implementation

- **Programming Language:** C  
- **Parallel Environment:** MPI  

### Key MPI Routines Used

- `MPI_Init`
- `MPI_Comm_rank`
- `MPI_Comm_size`
- `MPI_Bcast`
- `MPI_Scatter`
- `MPI_Gather`
- `MPI_Reduce`
- `MPI_Scan`
- `MPI_Finalize`

### Communication Model

- **Primary:** Collective communication  
- **Secondary:** Point-to-point blocking communication (used specifically for the prefix sum logic)

---

## Usage

### Compilation

Compile the source code using the MPI compiler wrapper:

```bash
mpicc -o collective_communication collective_communication.c
```

### Execution
Run the program with mpirun, specifying the number of processes:
```bash
mpirun -np 4 ./collective_communication
```
Important:

The vector size N must satisfy:

$$
𝑁
 
m
o
d
 
𝑝
=
0
$$

(i.e., N must be an integer multiple of the number of processes)

---

## Constraints & Limitations
### Data Distribution Constraint:
The current implementation does not support uneven vector sizes across processes.

### Scalability Limitation:
Handling cases where 

$$
𝑁
<
𝑝
$$

is not supported, as some processes would remain idle.

---

## Conclusion
This project demonstrates effective use of MPI collective communication for distributed numerical processing. It highlights practical applications of MPI_Bcast, MPI_Scatter, MPI_Reduce, and MPI_Scan, offering a strong foundation for understanding data-parallel computation and process coordination in high-performance computing environments.

---

## Open the Documentation
1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
    - English: `Collective-Communication.pdf`
    - Greek: `Συλλογική-Επικοινωνία.pdf`




