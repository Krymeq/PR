#include <vector>
#include <iostream>
#include <chrono>
#include <omp.h>


std::vector<uint32_t> primes(uint32_t begin, uint32_t end, int num_threads) {
	std::vector<bool> isComposite(end - 1, false);
	int count = 0;

	// Flag composite numbers
	#pragma omp parallel for
	for (int i = 0; i < num_threads; i++) {
		for (int divisor = 2 + i; divisor < end / 2; divisor += num_threads) {
			if (isComposite.at(divisor - 2)) continue;
			else {
				for (int num = divisor * 2; num <= end; num += divisor) {
					isComposite.at(num - 2) = true;
				}
			}
		}
	}

	// count prime numbers
	for (int i = begin - 2; i < isComposite.size(); i++) {
		if (!isComposite.at(i)) count++;
	}

	// Write prime numbers to the vector
	std::vector<uint32_t> output(count, 0);
	for (int i = begin - 2, index = 0; i < isComposite.size(); i++) {
		if (!isComposite[i]) {
			output.at(index) = (i + 2);
			index++;
		}
	}

	return output;
}



int main()
{
	int min = 2;
	int max = 5000000;
	int unitsAmount = 4;

	if (unitsAmount < 1)
		exit(-1);

	omp_set_num_threads(unitsAmount);

	std::vector<uint32_t> result = primes(min, max, unitsAmount);

	return 0;
}

