#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

void report(int i, int j)
{
    printf("Thread ID=%d: C(i,j)=C(%d,%d)\n",
        omp_get_thread_num(), i, j);
}

int main(int argc, char *argv[])
{
    #pragma omp parallel num_threads(4)
    {
        #pragma omp master
        {
            printf("Thread ID=%d: Number of threads=%d\n",
                omp_get_thread_num(), omp_get_num_threads());
        }

        #pragma omp barrier 

        #pragma omp for
        for (int i=0; i<3; i++) 
        {
            for (int j=0; j<6; j++) 
            {
                report(i, j);
            }
        }
    }

    return(0);
}

