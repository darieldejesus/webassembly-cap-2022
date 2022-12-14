#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <emscripten.h>

#define DEBUG 0

extern "C" {
	struct thread_args {
		int start;
		int end;
		std::vector<int> primes_found;
	};

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
		if (start % 2 == 0) {
			start++;
		}
		for (int i = start; i <= end; i += 2) {
			if (is_prime(i)) {
				primes_found.push_back(i);
			}
		}
	}

	void* thread_func(void* arg) {
		struct thread_args* args = (struct thread_args*)arg;
		find_primes(args->start, args->end, args->primes_found);
		return arg;
	}

	int main() {
		int start = 3;
		int end = 10000000;
		printf("Prime numbers between %d and %d: \n", start, end);

		std::chrono::high_resolution_clock::time_point duration_start =
			std::chrono::high_resolution_clock::now();

		pthread_t thread_ids[4];
		struct thread_args args[5];

		int args_index = 1;
		int args_start = 2000000;

		for (int i = 0; i < 4; i++) {
			args[args_index].start = args_start;
			args[args_index].end = args_start + 1999999 ;

			if (pthread_create(
					&thread_ids[i],
					NULL,
					thread_func,
					&args[args_index]
			)) {
				perror("Thread create failed.");
				return 1;
			}

			args_index += 1;
			args_start += 2000000;
		}

		find_primes(3, 1999999, args[0].primes_found);

		for (int j = 0; j < 4; j++) {
			pthread_join(thread_ids[j], NULL);
		}

		std::chrono::high_resolution_clock::time_point duration_end =
			std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> duration = duration_end - duration_start;

		printf("Process took %f milliseconds to execure.\n", duration.count());

		if (DEBUG == 1) {
			printf("The values found:\n");
			for (int k = 0; k < 5; k++) {
				for (int n : args[k].primes_found) {
					printf("%d ", n);
				}
			}
			printf("\n");
		}

		return 0;
	}
}
