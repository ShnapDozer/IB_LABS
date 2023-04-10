#include "rsa.h"

#include <iostream>
#include <cmath>
#include <QDebug>

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


// Есть проблема с шифрованием тк появляются очень большие степени, которые не укладываются в long long int и другие классы,
// поэтому шифрование потока байтов на данный момент недоступна из-за сложностей с длинной арифметикой.
void RSA::encrypt(char *rbuffer, long long int *wbuffer, const int bufSize)
{
    for(int i = 0; i < bufSize; ++i) {
        wbuffer[i] = ((long long int)pow(rbuffer[i], e)) % n;
    }
}

void RSA::decrypt(long long int *rbuffer, char *wbuffer, const int bufSize)
{
    for(int i = 0; i < bufSize; ++i) {
        wbuffer[i] = char(((long long int)pow(rbuffer[i], d)) % n);
    }
}
