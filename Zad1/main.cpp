#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 100000000;
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double x, pi, sum = 0.0;
	volatile double tab[52];
	int i;

	omp_set_num_threads(2);
	step = 1. / (double)num_steps;

	for (int j = 0; j < 50; j++) {
		tab[j] = 0.0;
		tab[j + 1] = 0.0;
		start = clock();
		#pragma omp parallel
		{
			#pragma omp for private(x)
			for (i = 0; i < num_steps; i++) {
				x = (i + 0.5) * step;
				tab[j + omp_get_thread_num()] += 4.0 / (1.0 + x * x);
			}
			pi = tab[j] * step;
			stop = clock();
			printf("iteracja: %d, %f sekund\n", j, ((double)(stop - start) / 1000.0));
		}
	}
	
	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	return 0;
}