#include <vector>
#include <iostream>
#include <chrono>

std::vector<uint32_t> primes(uint32_t begin, uint32_t end) {
	std::vector<bool> isComposite(end - 1, false);
	int count = 0;


	// Flag composite numbers
	for (int divisor = 2; divisor < end / 2; divisor++) {
		if (isComposite.at(divisor - 2)) continue;
		else {
			for (int num = divisor * 2; num <= end; num += divisor) {
				isComposite.at(num - 2) = true;
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
	std::vector<uint32_t> primes_arr = primes(2, 5000000);
	
	/*for (int i = primes_arr.size() - 10; i < primes_arr.size(); i++) {
		printf("%d: %d\n", i, primes_arr[i]);
	}*/

	return 0;
}

