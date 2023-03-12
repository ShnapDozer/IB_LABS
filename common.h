#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

namespace Common {
    void countFileSize(std::string filePath);
    void countFreq(std::string filePath);
    void countRelativeFreq(std::string filePath);
    void encrypt(std::string inPath, std::string outPath, int key[], const int keySize, bool encrypt = true);
    std::vector<int> getPrimeVec(int end);
    int NOD(int a, int b);
    bool isMutuallyPrime(int a, int b);
}

#endif // COMMON_H
