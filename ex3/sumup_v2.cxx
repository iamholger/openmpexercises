#include <cstdio>
#include "omp.h"

unsigned long crosscheck(unsigned long N)
{
    return N*(N+1)/2;
}

int main()
{
    unsigned long N = 1000000000;
    unsigned long result = 0;
    
    #pragma omp parallel default(none)
    {
        unsigned long temp = 0;
  
        #pragma omp for 
        for (unsigned long i=1;i<N+1;i++)
        {
            temp += i;
        }

        #pragma omp critical
        result += temp;
    }

    printf("Result:    %lu\n", result);
    printf("Should be: %lu\n", crosscheck(N));

    return 0;
}
