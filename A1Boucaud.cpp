#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <fstream>
#include <time.h> 

void sieveOfEratosthenes(int n, std::vector<bool>& primes, std::atomic<int>& count, std::atomic<long long>& sum, int start, int end) {
    for (int p = 2; p * p <= n; p++) {
        if (primes[p]) {
            for (int i = p * 2; i <= n; i += p) {
                primes[i] = false;
            }
        }
    }
    
    for (int i = start; i <= end; i++) {
        if (primes[i]) {
            count.fetch_add(1, std::memory_order_relaxed);
            sum.fetch_add(i, std::memory_order_relaxed);
        }
    }
}

int main() {
    clock_t startTime, endTime;
    double cpu_time_used;

    startTime = clock(); 

    const int n = 100000000; 
    std::vector<bool> primes(n + 1, true);
    std::atomic<int> count(0);
    std::atomic<long long> sum(0);

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; i++) {
        int start = (n / numThreads) * i + 2;
        int end = (n / numThreads) * (i + 1) + 1;

        if (end > n) {
            end = n;
        }

        threads.emplace_back(sieveOfEratosthenes, n, std::ref(primes), std::ref(count), std::ref(sum), start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    endTime = clock(); 
    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC; 

    std::ofstream myfile;
    myfile.open ("primes.txt");
    myfile << count << sum << cpu_time_used << "\n";
    myfile.close();

    return 0;
}