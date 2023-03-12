#ifndef RSA_H
#define RSA_H

#include "common.h"

class RSA
{
public:
    struct Key {
        int firstNumber;
        int SecondNumber;
    };

    RSA();
    ~RSA();

    void generateKey(int p, int q);
    void encrypt(char* buffer, const int bufSize);
    void decrypt(char* buffer, const int bufSize);
    Key getPublicKey() const { return publicKey; }
    Key getPrivateKey() const { return privateKey; }

private:
    int p, q, n, e, d;
    Key publicKey;
    Key privateKey;
};

#endif // RSA_H
