#include "stdafx.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <omp.h>


std::vector<uint32_t> primes(uint32_t begin, uint32_t end) {
	std::vector<bool> isComposite(end - begin, false);

	// Flag composite numbers
	for (int divisor = 2; divisor < end; divisor++) {

		for (int num = begin; num < end; num++) {
			if (num % divisor == 0 && num != divisor) {
				isComposite.at(num - begin) = true;
			}
		}
	}

	// Write prime numbers to the vector
	std::vector<uint32_t> output;
	for (int i = 0; i < end - begin; i++) {
		if (!isComposite[i]) {
			output.push_back(i + begin);
		}
	}

	return output;
}



int main()
{
	int min = 2;
	int max = 100002;
	int unitsAmount = 4;
	int primesPerStep = (max - min) / unitsAmount;
	std::vector<uint32_t> result;	
	
	// yeah cool zobaczmy co się stanie jak każemy mu się wykonać na minus dwóch procesorach XD
	if (unitsAmount < 1)
		exit(-1);

	omp_set_num_threads(unitsAmount);
	auto start = std::chrono::high_resolution_clock::now();

	#pragma omp parallel for
	for (int x = 0; x < unitsAmount; x++) {
		std::vector<uint32_t> out = primes((primesPerStep * x) + min, (primesPerStep * (x + 1)) + min - 1);
		
		#pragma omp critical 
		result.insert(result.end(), out.begin(), out.end());
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (stop - start);

	printf("Time elapsed: %d ms.\n", duration.count());
/*
	for (int i = 0; i < result.size(); i++) {
		printf("%d: %d\n", i, result[i]);
	}*/
	

	system("PAUSE");
	return 0;
}

