#include "rsa.h"
#include <iostream>
#include <cmath>

RSA::RSA() : p(-1), q(-1), n(-1)
{

}

RSA::~RSA()
{

}

void RSA::generateKey(int p, int q)
{
    n = p*q;
    int eFunc = (p-1)*(q-1);

    auto primeVec = Common::getPrimeVec(eFunc);
    for(auto i = primeVec.rbegin(); i < primeVec.rend(); ++i) {
        if(Common::isMutuallyPrime(*i, eFunc)){
            e = *i;
        }
    }

    if (e != -1 && n != -1) {
        publicKey = {e, n};

        int k = 1;
        while((k*eFunc + 1) % e != 0) {
            ++k;
        }
        d = (k*eFunc + 1) / e;

        privateKey = {d, n};
    } else {
        std::cout << "Something wrong, while generate key";
    }
}

void RSA::encrypt(char *buffer, const int bufSize)
{
    for(int i = 0; i < bufSize; ++i) {
        buffer[i] = char(((int)pow(buffer[i], e)) % n);
        std::cout << ((int)pow(buffer[i], e)) % n << " ";
    }
    std::cout << std::endl;
}

void RSA::decrypt(char *buffer, const int bufSize)
{
    for(int i = 0; i < bufSize; ++i) {
        buffer[i] = char(((int)pow(buffer[i], d)) % n);
        std::cout << ((int)pow(buffer[i], e)) % n << " ";
    }
    std::cout << std::endl;
}
