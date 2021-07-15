#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

//****************************************************************************80
int main ( int argc, char *argv[] )
//****************************************************************************80
{
    int x(100);
    printf("The initial value of x: %d\n", x);

    #pragma omp parallel for private(x)
    for(int i=0; i<10; i++){
        printf("Thread number: %d     x (before): %d\n",omp_get_thread_num(),x);
        x=i;
        printf("Thread number: %d     x (after): %d\n",omp_get_thread_num(),x);
    }

    printf("The final value of x: %d\n", x);

    return 0;
}

