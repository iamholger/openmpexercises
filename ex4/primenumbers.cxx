//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    21 May 2009
//
//  Author:
//
//    John Burkardt
//
//  Modified by HS  
#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>


using namespace std;


// A function that counts the number of prime numbers in the range from 2 to n
int count_prime_numbers(int n)
{
  int total = 0; // This is our shared accumulator we reduce into

#pragma omp parallel for default(none) shared(n) reduction (+:total)
  for (int i=2; i<=n; i++)  // test all integers in [2,n] in parallel
  {
    int is_prime=1;  

    for (int j=2; j<i; j++)   // This loop tests if i is a prime number
    {
      if ( i%j == 0 )            // As soon as we find a divisor, we can
      {                          //  exit this for loop as i is then not a prime number
        is_prime = 0;            //  we set is_prime to 0 in this case so that total is not changed
        break;                 // This exits the j-loop early
      }
    }
    total = total + is_prime; // The logic here is, if i happened to be a prime number,
                              // we increment total by one, if not we add a 0.
  }

  return total;
}


int main ( int argc, char *argv[] )
{
  double t_0 = omp_get_wtime ( );

  if (argc!=2)
  {
     printf("Error, you need to provide exactly one command line argument.\n");
     exit(1);
  }

  // Get the upper limit on the search interval from the user
  int nmax = std::atoi(argv[1]);

  // This simulates a serial program phase by simply sleeping for 0.1 seconds
  // In real applications this could be reading data from files, for example.
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // This calls the prime number counting function
  int nprimes = count_prime_numbers(nmax);

  printf("Found %d prime numbers in the range [1,%d]\n", nprimes, nmax);
  
  // This simulates a serial program phase by simply sleeping for 0.1 seconds
  // In real applications this could be writing data to files, for example.
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  printf("Program took %f seconds.\n", omp_get_wtime() - t_0);

 exit(0);
}
