#ifndef RSA_H
#define RSA_H

#include "common.h"

class RSA
{
public:
    struct Key {
        long int firstNumber;
        long int SecondNumber;
    };

    RSA();
    ~RSA();

    void generateKey(int p, int q);
    void encrypt(char *rbuffer, long long int *wbuffer, const int bufSize);
    void decrypt(long long int *rbuffer, char *wbuffer, const int bufSize);
    Key getPublicKey() const { return publicKey; }
    Key getPrivateKey() const { return privateKey; }

private:
    long long int p, q, n, e, d;
    Key publicKey;
    Key privateKey;
};

#endif // RSA_H
