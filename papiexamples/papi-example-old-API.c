#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

#define NUM_EVENTS 4

void matmul(const double *A, const double *B,
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
}


int main(int argc, char ** argv)
{
    const int size = 300;
    double a[size][size];
    double b[size][size];
    double c[size][size];

    int retval;
    int EventSet = PAPI_NULL;
    int numEvents = 1;
    //long long values[1];
    long long count;

    /* Init PAPI library */
    retval = PAPI_library_init( PAPI_VER_CURRENT );
    if ( retval != PAPI_VER_CURRENT ) {
        printf("Error 1\n");
    }

    /* create the eventset */
    retval = PAPI_create_eventset( &EventSet );
    if ( retval != PAPI_OK ) {
        printf("Error 2\n");
    }

    //char event_name1[]="PAPI_TOT_CYC";
    char event_name1[]="PAPI_FP_INS";
    //char event_name1[]="PAPI_VEC_INS";
    retval = PAPI_add_named_event( EventSet, event_name1);
    if ( retval != PAPI_OK ) {
        printf("Error 3\n");
    }

    /*char event_name2[]="PAPI_TOT_INS";
    retval = PAPI_add_named_event( EventSet, event_name2);
    if ( retval != PAPI_OK ) {
        printf("Error 4\n");
    }*/

    /* Start PAPI */
    retval = PAPI_start( EventSet );
    if ( retval != PAPI_OK ) {
        printf("Error 5\n");
    }

    /* Benchmark code */
    matmul((double *)a, (double *)b, (double *)c, size, size, size);


    /* read results -1 */
    retval = PAPI_stop_counters(&count, numEvents);
    //retval = PAPI_stop( EventSet, values );
    if ( retval != PAPI_OK ) {
        printf("Error 6\n");
    }

    //printf("Total count %s: %lld\n", event_name1, values[0]);
    /*
    printf("Total instructions: %lld\n", values[0]);
    printf("Total cycles: %lld\n", values[1]);
    printf("Instr per cycle: %2.3f\n", (double)values[0] / (double) values[1]);
    */

    /* Cleanup */
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);

    return 0;
}
