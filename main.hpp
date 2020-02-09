#ifndef NBPREMIER_MAIN_HPP
#define NBPREMIER_MAIN_HPP

#include <math.h>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void eratosthene(std::vector<char> *, int, int);

void primeRange(int, int, std::vector<int> *);
int isPrime(int);

int countPrime(std::vector<char>);
void writeOutputFile(std::vector<char>);

#endif  // NBPREMIER_MAIN_HPP