#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

int main()
{
	omp_set_num_threads(3);

	#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		printf("Hello World from ID=%d!\n", id);
	}

	return 0;
}


