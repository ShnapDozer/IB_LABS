#include "common.h"
#include <iostream>
#include <cstdio>

using namespace std;

int Common::NOD(int a, int b)
{
    while(a > 0 && b > 0)

        if(a > b)
            a %= b;
        else
            b %= a;

    return a + b;
}

bool Common::isMutuallyPrime(int a, int b)
{
    return NOD(a, b) == 1;
}

std::vector<int> Common::getPrimeVec(int end)
{
    std::vector<int> primeNumbers;
    bool isPrime = true;

    for(int i = 2; i < end; ++i) {
        for(int j : primeNumbers) {
            if(i % j == 0) {
                isPrime = false;
                break;
            }
        }

        if(isPrime) {
            primeNumbers.push_back(i);
        }

        isPrime = true;
    }

    return primeNumbers;
}

void Common::encrypt(string inPath, string outPath, int key[], const int keySize, bool encrypt)
{
    if(encrypt) {
        cout << "---Encrypting..." << endl;
    } else {
        cout << "---Decrypting..." << endl;
    }

    FILE* inStream = fopen(inPath.c_str(), "rb");
    FILE* outStream = fopen(outPath.c_str(), "wb");

    if (!inStream) {
      printf("Error: could not open file %s\n", inPath.c_str());
      return;
    } else if(!outStream) {
        printf("Error: could not open file %s\n", outPath.c_str());
        return;
    }

    int readBytes = -1;
    char* rbuffer = new char[keySize];
    char* wbuffer = new char[keySize];

    while ((readBytes = fread(rbuffer, sizeof(char), keySize, inStream)) > 0) {

        if(readBytes < keySize) {
            for (int i = readBytes - 1; i < keySize; ++i) {
                  rbuffer[i] = 'z';
            }
        }

        if(encrypt) {
            for (int i = 0; i < keySize; ++i) {
                  wbuffer[i] = rbuffer[key[i]];
            }
        } else {
            for (int i = 0; i < keySize; ++i) {
                  wbuffer[key[i]] = rbuffer[i];
            }
        }
        fwrite(wbuffer, sizeof(char), keySize, outStream);
    }

    fclose(inStream);
    fclose(outStream);

    delete[] rbuffer;
    delete[] wbuffer;
}

void Common::countRelativeFreq(std::string filePath)
{
    cout << "---СountRelativeFreq..." << endl;

    FILE* fileStream = fopen(filePath.c_str(), "rb");
    if (!fileStream) {
      printf("Error: could not open file %s\n", filePath.c_str());
      return;
    }

    long long int charFreq[256];
    for (int i = 0; i < 256; ++i) {
      charFreq[i] = 0;
    }

    const int BUFFERSIZE = 4096;
    double fileSize = 0;
    int readBytes = -1;
    char* buffer = new char[BUFFERSIZE];

    while ((readBytes = fread(buffer, sizeof(char), BUFFERSIZE, fileStream)) > 0) {
      for (int i = 0; i < readBytes; ++i) {
            ++charFreq[buffer[i]];
            ++fileSize;
      }
    }

    for (int i = 0; i < 256; ++i) {
      if (charFreq[i] > 0) {
        cout << char(i) << charFreq[i] / fileSize << endl;
      }
    }

    fclose(fileStream);
    delete[] buffer;
}

void Common::countFreq(std::string filePath)
{
    cout << "---СountFreq..." << endl;

    FILE* fileStream = fopen(filePath.c_str(), "rb");
    if (!fileStream) {
      printf("Error: could not open file %s\n", filePath.c_str());
      return;
    }

    long long int charFreq[256];
    for (int i = 0; i < 256; ++i) {
      charFreq[i] = 0;
    }

    const int BUFFERSIZE = 4096;
    int readBytes = -1;
    char* buffer = new char[BUFFERSIZE];

    while ((readBytes = fread(buffer, sizeof(char), BUFFERSIZE, fileStream)) > 0) {
      for (int i = 0; i < readBytes; ++i) {
        ++charFreq[buffer[i]];
      }
    }

    for (int i = 0; i < 256; ++i) {
      if (charFreq[i] > 0) {
        cout << char(i) << charFreq[i] << endl;
      }
    }

    fclose(fileStream);
    delete[] buffer;
}

void Common::countFileSize(std::string filePath)
{
    cout << "---СountFileSize..." << endl;

    FILE* fileStream = fopen(filePath.c_str(), "rb");
    if (!fileStream) {
      printf("Error: could not open file %s\n", filePath.c_str());
      return;
    }

    const int BUFFERSIZE = 4096;
    int readBytes = -1;
    char* buffer = new char[BUFFERSIZE];
    long long int size = 0;

    while ((readBytes = fread(buffer, sizeof(char), BUFFERSIZE, fileStream)) > 0) {
        size += readBytes;
    }

    cout << "File size is " << size << endl;

    fclose(fileStream);
    delete[] buffer;
}
