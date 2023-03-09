#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define NPROBS 8

#define LEN 15
#define N 5
#define M 5


#define PRINT_RESULT_VECTOR( V, NAME ) {    \
    printf("%2s: ", NAME);                  \
    for (int i=0; i<LEN; i++)               \
        printf("%4d ", V[i]);               \
    printf("\n");                           \
}

#define PRINT_RESULT_MATRIX(MAT, NAME) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<N; i++) {               \
        for (int j=0; j<M; j++)             \
            printf("%4d ", MAT[i*M+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}

// -------- uncomment these two lines when solutions are published --------
// #include "../../solutions/lab1_sol.cu"
// #define RESULTS
// ------------------------------------------------------------------------

#ifndef SOLUTION_STACKVEC_1
#define SOLUTION_STACKVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_1
#define SOLUTION_HEAPVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_2
#define SOLUTION_HEAPVEC_2 { }
#endif

#ifndef SOLUTION_STACKVEC_2
#define SOLUTION_STACKVEC_2 { }
#endif

#ifndef SOLUTION_STACKMAT_1
#define SOLUTION_STACKMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_1
#define SOLUTION_HEAPMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_2
#define SOLUTION_HEAPMAT_2 { }
#endif

#ifndef SOLUTION_STACKMAT_2
#define SOLUTION_STACKMAT_2 { }
#endif

void sum_vector(int* a, int* b, int* c) {
    for (int i=0; i<LEN; i++)
        c[i] = a[i] + b[i];
}

int* sum_vector2(int* a, int* b) {
    int* c = (int*)malloc(LEN * sizeof(int));
    for (int i=0; i<LEN; i++)
        c[i] = a[i] + b[i];
    return c;
}

int* sum_vector3(int* a, int* b) {
    static int c[LEN];
    for (int i=0; i<LEN; i++)
        c[i] = a[i] + b[i];
    return c;
}

int* sum_matrix(int* A, int* B, int* C) {
    for (int i=0; i<N*M; i++)
        C[i] = A[i] + B[i];
    return C;
}

int* sum_matrix2(int* A, int* B) {
    int* C = (int*)malloc(N*M * sizeof(int));
    for (int i=0; i<N*M; i++)
        C[i] = A[i] + B[i];
    return C;
}

int* sum_matrix3(int* A, int* B) {
    static int C[N*M];
    for (int i=0; i<N*M; i++)
        C[i] = A[i] + B[i];
    return C;
}

int main(void) {
    // ---------- for timing ----------
    float CPU_times[NPROBS];
    for (int i=0; i<NPROBS; i++)
        CPU_times[i] = 0.0;
    struct timeval temp_1, temp_2;
    // --------------------------------

#ifdef RESULTS
    printf("You are now running the \x1B[31mSOLUTION CODE\x1B[37m:\n");
#else
    printf("You are now running \x1B[31mYOUR CODE\x1B[37m:\n");
#endif
    // ---------------------- Stack vectors 1 ----------------------
    /* Generate three stack vectors a, and b of length "LEN" such
     * that for each i in {0, 1, ... LEN-1} a[i] = i, b[i] = 100 * i.
     * Then compute the vector c = a + b.
     */

#ifdef RESULTS
        SOLUTION_STACKVEC_1
        PRINT_RESULT_VECTOR(c, "c")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int a[LEN], b[LEN], c[LEN];
    for (int i=0; i<LEN; i++)
        a[i] = i;
    for (int i=0; i<LEN; i++)
        b[i] = 100 * i;
    for (int i=0; i<LEN; i++)
        c[i] = a[i] + b[i];

    gettimeofday(&temp_2, NULL);
    CPU_times[0] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.0;
    PRINT_RESULT_VECTOR(c, "c");

#endif
    // ---------------------- Heap vectors 1 -----------------------
    /* Compute the same result as c but in a heap vector c1 allocated
     * in the main but computed in an extern function.
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_1
    PRINT_RESULT_VECTOR(c1, "c1")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    
    gettimeofday(&temp_1, NULL);

    int* c1 = (int*)malloc(LEN * sizeof(int));
    sum_vector(a, b, c1);

    gettimeofday(&temp_2, NULL);
    CPU_times[1] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_VECTOR(c1, "c1");
    free(c1);


#endif
    // ---------------------- Heap vectors 2 -----------------------
    /* Compute the same result as c and c1 in a heap vector c2
     * also allocated in the extern function
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_2
    PRINT_RESULT_VECTOR(c2, "c2")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int* c2 = sum_vector2(a, b);

    gettimeofday(&temp_2, NULL);
    CPU_times[2] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_VECTOR(c2, "c2");
    free(c2);

#endif
    // ---------------------- Stack vectors 2 ----------------------
    /* Is it possible to compute the c vector as a stack vector of
     * the extern function and then return it to the main?
     */
#ifdef RESULTS
    SOLUTION_STACKVEC_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int* c3 = sum_vector3(a, b);

    gettimeofday(&temp_2, NULL);
    CPU_times[3] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_VECTOR(c3, "c3");

#endif


    /* Do now the same 4 previous exercises but with the three
     * matrices A, B, C of N rows and M columns where:
     *   1) A[i][j] = i + j
     *   2) B[i][j] = (i + j) * 100
     *   3) C = A + B
     *
     * What are the differences when you change from vectors to
     * matrices?
     */
    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_1
        PRINT_RESULT_MATRIX(((int*)C), "C")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int A[N][M], B[N][M], C[N][M];
    for (int i=0; i<N*M; i++)
        ((int*) A)[i] = i;
    for (int i=0; i<N*M; i++)
        ((int*) B)[i] = (i) * 100;
    for (int i=0; i<N*M; i++)
        ((int*) C)[i] = ((int*) A)[i] + ((int*) B)[i];

    gettimeofday(&temp_2, NULL);
    CPU_times[4] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_MATRIX(((int*)C), "C");


#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_1
        PRINT_RESULT_MATRIX(C1, "C1")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int* C1 = (int*)malloc(N*M * sizeof(int));
    sum_matrix((int*)A, (int*)B, C1);

    gettimeofday(&temp_2, NULL);
    CPU_times[5] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_MATRIX(C1, "C1");
    free(C1);


#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_2
        PRINT_RESULT_MATRIX(C2, "C2")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

    gettimeofday(&temp_1, NULL);

    int* C2 = sum_matrix2((int*)A, (int*)B);

    gettimeofday(&temp_2, NULL);
    CPU_times[6] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_MATRIX(C2, "C2");
    free(C2);

#endif

    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */
    gettimeofday(&temp_1, NULL);

    int* C3 = sum_matrix3((int*)A, (int*)B);

    gettimeofday(&temp_2, NULL);
    CPU_times[7] = ((temp_2.tv_sec - temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec))/1000000.;
    PRINT_RESULT_MATRIX(C3, "C3");

#endif

    for (int i=0; i<NPROBS; i++) {
        printf("Problem %d runs in %9.8f CPU time\n", i, CPU_times[i]);
    }
    printf("\n");

    return(0);
}
