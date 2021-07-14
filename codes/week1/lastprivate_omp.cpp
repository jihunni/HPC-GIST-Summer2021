#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

//****************************************************************************80
int main ( int argc, char *argv[] )
//****************************************************************************80
{
  int i;
  int x;

  x=44; 

  #pragma omp parallel for lastprivate(x)
  for(i=0;i<=10;i++){
    x=i;
    printf("Thread number: %d     x: %d\n",omp_get_thread_num(),x);
  }     

  printf("x is %d\n", x);

  return 0;

}

