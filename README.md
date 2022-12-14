# Calculate Primes - CAP 2022

### Requirements
- [Python3](https://www.python.org/downloads/)
- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)

### Sequential Execution

- Command to compile the sequential version:
```bash
emcc calculate_primes_sequential.cpp -O1 -std=c++11 -o build/calculate_primes_sequential.html
```

- Run HTTP server for accessing the calculate_primes_sequential.html file via http://localhost:8080/build/calculate_primes_sequential.html
```bash
python3 server.py
```

- The process to calculate primes is started as soon as you open the `pthreads.html` page.
```
Prime numbers between 3 and 10000000: 
Process took 3738.055000 milliseconds to execure.
```

### Parallel Execution

- Command to compile the parallel version:
```bash
emcc calculate_primes_parallel.cpp -O1 -std=c++11 -s INITIAL_MEMORY=256MB -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -o build/calculate_primes_parallel.html
```

- Run HTTP server for accessing the pthreads.html file via http://localhost:8080/build/calculate_primes_parallel.html
```bash
python3 server.py
```

- The process to calculate primes is started as soon as you open the `calculate_primes_parallel.html` page.
```
Prime numbers between 3 and 10000000: 
Process took 1102.255001 milliseconds to execure.
```
