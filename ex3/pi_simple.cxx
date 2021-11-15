/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99. Modified by HS 11/21.

*/
#include <cstdio>
#include <omp.h>


int main() {

  // Numerical integration of f(x) = 4/(1+x^2) in [a,b] = [0,1]
  // We use a fixed stepsize ('delta x') here.

  const long num_steps = 500000000;
  const double a=0;
  const double b=1;
  const double stepsize = (b-a) / num_steps; // This is 'delta x'

  double sum = 0;   // This accumulates the f(x)*'delta x' values (i.e. areas)
   
  double t_0 = omp_get_wtime(); // time stamp

  #pragma omp parallel for // reduction(*:sum)
  for (int i = 1; i <= num_steps; i++) 
  {
    double x = a + (i - 0.5) * stepsize;
//#pragma opm atomic
    sum += 4.0 / (1.0 + x * x) * stepsize;   // evaluate f(x)*'delta x' and add to accumulator
  }
  
  double t_tot = omp_get_wtime() - t_0; // duration in seconds

  printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, sum, t_tot);
}
