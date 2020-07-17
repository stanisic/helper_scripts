#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

// For PAPI 5.7

#define NUM_EVENTS 3
#define SIZE 300

long long cube(long long x) {return x*x*x;}

double matmul(const double *A, const double *B,
            double *C, int m, int n, int p)
{
    int i, j, k;
    for (i = 0; i < m; ++i)
        for (j = 0; j < p; ++j) {
            double sum = 0;
            for (k = 0; k < n; ++k)
                sum += A[i*n + k] * B[k*p + j];
            C[i*p + j] = sum;
        }
    return C[SIZE*SIZE-1];
}


int main(int argc, char ** argv)
{
    /* Matrices of the program*/
    double a[SIZE][SIZE];
    double b[SIZE][SIZE];
    double c[SIZE][SIZE];
    double result = 0;

    /* PAPI variables */
    int Events[NUM_EVENTS] = {PAPI_TOT_CYC, PAPI_VEC_INS, PAPI_FP_INS};
    char event_names[NUM_EVENTS][100] = {"PAPI_TOT_CYC", "PAPI_VEC_INS", "PAPI_FP_INS"};
    long long values[NUM_EVENTS];

    /* Start PAPI */
    if (PAPI_start_counters(Events, NUM_EVENTS) != PAPI_OK)
        printf("Error start\n");

    /* Benchmark code */
    result = matmul((double *)a, (double *)b, (double *)c, SIZE, SIZE, SIZE);
    printf("Printing result to avoid compiler ignoring whole function %f\n", result);

    /* Stop and read PAPI */
    if ( PAPI_stop_counters(values, NUM_EVENTS) != PAPI_OK )
        printf("Error stop\n");

    /* Print PAPI */
    for (int i=0; i<NUM_EVENTS; i++)
       printf("Total count %s: %lld\n", event_names[i], values[i]);

    /* Helper for comparison */
    printf("Expected FLOP count %lld\n", cube(SIZE-1) + cube(SIZE));

    return 0;
}
