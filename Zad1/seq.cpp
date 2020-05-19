#include "stdafx.h"
#include <vector>
#include <iostream>


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
	int count = 0;
	for (int i = 0; i < end - begin; i++) {
		if (!isComposite[i]) {
			output.push_back(i + begin);
			count++;
		}
	}

	return output;
}


int main()
{
	std::vector<uint32_t> primes_arr = primes(2, 50);
	for (int i = 0; i < primes_arr.size(); i++) {
		printf("%d: %d\n", i, primes_arr[i]);
	}

	system("PAUSE");
    return 0;
}

