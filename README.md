# Assignment14520

This code finds prime numbers up to a value "n" using a method called the Sieve of Eratosthenes. This method basically goes through numbers and marks the non-prime ones by using the fact that, for example, after it reads 2, it knows all multiples of 2 are also not prime. So, in the end, we only have prime numbers left.

I divided this process among different threads based on how many our system supports (using hardware concurrency!). This makes it faster because more threads are working on the task. Each thread works on a specific range of numbers, ensuring they don't overlap and work is divided evenly.

I record the time taken to find all those prime numbers. I save this time, the total number of primes found (count), and their sum in a file called "primes.txt". The average time I got was about 13 seconds, which is way better than what I got before I changed to the Sieve of Eratosthenes.

To run this program, since it is a C++ program:
Compile the C++ program using a compiler (e.g., `g++ filename.cpp -o outputfile -std=c++11 -pthread`).
Run the compiled program in your terminal (e.g., `./outputfile`).

## Output
The program will create a text file named 'primes.txt'. This file will contain:

- The total count of prime numbers found.
- The sum of all these prime numbers.
- The time taken to find these primes.
