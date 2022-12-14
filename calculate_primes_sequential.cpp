#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <emscripten.h>

#define DEBUG 0

extern "C" {
	int is_prime(int value) {
		if (value == 2) {
			return 1;
		}
		if (value <= 1 || value % 2 == 0) {
			return 0;
		}
		for (int i = 3; (i * i) <= value; i += 2) {
			if (value % i == 0) {
				return 0;
			}
		}
		return 1;
	}

	void find_primes(int start, int end, std::vector<int>& primes_found) {
		for (int i = start; i <= end; i += 2) {
			if (is_prime(i)) {
				primes_found.push_back(i);
			}
		}
	}

	int main() {
		int start = 3;
		int end = 10000000;
		printf("Prime numbers between %d and %d: \n", start, end);

		std::chrono::high_resolution_clock::time_point duration_start =
			std::chrono::high_resolution_clock::now();

		std::vector<int> primes_found;
		find_primes(start, end, primes_found);

		std::chrono::high_resolution_clock::time_point duration_end =
			std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> duration = duration_end - duration_start;

		printf("Process took %f milliseconds to execure.\n", duration.count());

		if (DEBUG == 1) {
			printf("The values found:\n");
			for (int n : primes_found) {
				printf("%d ", n);
			}
			printf("\n");
		}

		return 0;
	}
}
