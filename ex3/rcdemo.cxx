#include <cstdio>

int main() {
    int a=10;
    #pragma omp parallel
    {
        a = a+1;
    }
    printf("Final result a=%d\n", a);
    return 0;
}
