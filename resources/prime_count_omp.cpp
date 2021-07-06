# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <omp.h>

using namespace std;

//****************************************************************************80
int prime_count ( int n )
//****************************************************************************80
{
    int i, j, prime, total_prime=0;

    #pragma omp parallel for reduction(+:total_prime) \
                             schedule(static) private(i, j, prime)
    for ( i = 2; i <= n; i++ ) {
        prime = 1;
        for ( j = 2; j < i; j++ ) {
            if ( i % j == 0 ) {
                prime = 0;
                break;
            }
        }
        total_prime += prime;
    }
    return total_prime;
}

//****************************************************************************80
int main (int argc, char *argv[])
//****************************************************************************80
{
    int n, num_procs, num_threads, total_prime=0;
    double start, end;

    // Returns the number of processors that are available to the program
    num_procs = omp_get_num_procs();

    // Returns the maximum value that can be returned by a call to the OMP_GET_NUM_THREADS function
    num_threads = omp_get_max_threads();

    cout << "\n";
    cout << "SCHEDULE_OPENMP\n";
    cout << "  C++/OpenMP version\n";
    cout << "  Count the primes from 1 to N.\n";
    cout << "  This is an unbalanced work load, particular for two threads.\n";
    cout << "  Demonstrate static and dynamic scheduling.\n";
    cout << "\n";
    cout << "  Number of processors available = " << num_procs << "\n";
    cout << "  Number of threads =              " << num_threads << "\n\n";
    cout << "Type N and enter: ";
    cin >> n ;

    start = omp_get_wtime();  // start time check
    total_prime = prime_count(n);
    end = omp_get_wtime();    // end time check

    cout << "  " << setw(8) << "N"
         << "  " << setw(18) << "Count of primes"
         << "  " << setw(18) << "Numer of threads"
         << "  " << setw(30) << "Elapsed wall clock time (sec)" << "\n";

    cout << "  " << setw(8) << n
         << "  " << setw(18) << total_prime
         << "  " << setw(18) << num_threads
         << "  " << setw(30) << end-start << "\n";

    return 0;
}
