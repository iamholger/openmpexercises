#include <cstdio>
#include "omp.h"

int main()
{
    unsigned long N = 1000000000;

    unsigned long SUMS[4] = {0,0,0,0};

#pragma omp parallel for
    for (unsigned long i=1;i<N+1;i++)
    {
        SUMS[omp_get_thread_num()]+=i;
    }

    unsigned long result = SUMS[0] + SUMS[1] + SUMS[2] + SUMS[3];

    printf("Result: %lu\n", result);

    return 0;
}
