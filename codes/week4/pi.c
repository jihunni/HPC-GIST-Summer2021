#include <stdio.h>
#include <time.h>

void Pi(int num_steps) 
{
  double begin, end, elapsed,  pi, step, x, sum;
  int i;
  begin = clock();
  step = 1.0/(double)num_steps;
  sum = 0;
  for (i=0;i<num_steps;i++) {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  end = clock();
  elapsed = (float)(end-begin)/CLOCKS_PER_SEC;
  printf("Pi with %d steps is %f in %f secs\n", num_steps, pi,elapsed);
}

int main() {
  Pi(100000000);
  return 0;
}
