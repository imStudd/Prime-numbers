#include "main.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage ./prime [N] [NB_THREAD]" << std::endl;
        exit(1);
    }

    int n = std::atoi(argv[1]);
    int nbThread = std::atoi(argv[2]);

    std::vector<char> vec(n, 1);
    std::vector<std::thread> vecThread;
    // std::vector<int> results; // naive method

    for (int i = 0; i < nbThread; ++i) {
        vecThread.emplace_back(eratosthene, &vec, 3 + (2 * i), nbThread * 2);
        // vecThread.emplace_back(primeRange, (((float)n / nbThread)* i), ((float)n / nbThread) * (i + 1), &results);
    }

    for (int i = 0; i < nbThread; ++i) {
        vecThread[i].join();
    }

    writeOutputFile(vec);

    printf("Number of prime: %d\n", countPrime(vec));

    return 0;
}

/**
 * naive method
 */
void primeRange(int a, int b, std::vector<int> *result) {
    for (int i = a; i < b; ++i) {
        if (isPrime(i)) {
            result->push_back(i);
        }
    }
}

/*
 * Function to calculate if a number is a prime number.
 * @return: 1 if n is a prime number
 *          0 if n isn't a prime number
 */
int isPrime(int n) {
    if (n <= 3) return n > 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

/*
 * Implementation of the Sieve of Eratosthenes.
 * @param: pointer of vector of char init to 1
 *         (integer)
 *         (integer)
 */
void eratosthene(std::vector<char> *vec, int start, int step) {
    for (size_t i = start; i * i < vec->size(); i += step) {
        if ((*vec)[i]) {
            for (size_t j = i * i; j < vec->size(); j += i) {
                if ((*vec)[j]) (*vec)[j] = 0;
            }
        }
    }
}

/*
 * Function wich count the prime numbers.
 * @param: vector of char
 * @return: prime numbers (integer)
 */
int countPrime(std::vector<char> vec) {
    // init to 1 to count '2'
    int n = 1;

    // loop on odd numbers
    for (size_t i = 3; i < vec.size(); i += 2) {
        if (vec[i] == 1) {
            ++n;
        }
    }
    return n;
}

/*
 * Function to write results in file(s).
 * @param: vector of char
 */
void writeOutputFile(std::vector<char> vec) {
    std::ofstream file("results_16705068.txt");
    std::string buffer;
    int step = 1, nb = 1;

    buffer.append("2\n");

    // loop on odd numbers
    for (size_t i = 3; i < vec.size(); i += 2) {
        if (vec[i] == 1) {
            if (step > 10000000) {
                file.write(buffer.data(), buffer.size());
                file.close();
                buffer.clear();
                file = std::ofstream("results_" + std::to_string(nb) + "_16705068.txt");
                ++nb;
                step = 0;
            }
            buffer.append(std::to_string(i) + '\n');
            ++step;
        }
    }
    file.write(buffer.data(), buffer.size());
    file.close();
}