#include <cstdio>

int main() {
    int sum=0;
    const int N=100;

    #pragma omp parallel for
    for (int n=1;n<N+1;n++)
    {
      sum +=n;         // Race condition here
    }
    printf("Result is %d. It should be %d\n", sum, N*(N+1)/2);
    return 0;
}
