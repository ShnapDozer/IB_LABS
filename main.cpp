#include <iostream>
#include "common.h"
#include "rsa.h"

using namespace std;

int main(int argc, char* argv[])
{
    RSA keys;
    keys.generateKey(2, 31);

    cout << "PublicKey is " << keys.getPublicKey().firstNumber << " " << keys.getPublicKey().SecondNumber <<endl;
    cout << "PrivateKey is " << keys.getPrivateKey().firstNumber << " " << keys.getPrivateKey().SecondNumber << endl;

    const int bufSize = 3;
    char* rbuffer = new char[bufSize] {'0', '1', '1'};
    long long int *ibuffer = new long long int[bufSize];

    for(int i = 0; i < bufSize; ++i) {
        cout << (int)rbuffer[i] << " ";
    }
    cout << endl;

    keys.encrypt(rbuffer,ibuffer, bufSize);
    for(int i = 0; i < bufSize; ++i) {
        cout << (int)rbuffer[i] << " ";
    }
    cout << endl;

    keys.decrypt(ibuffer, rbuffer, bufSize);
    for(int i = 0; i < bufSize; ++i) {
        cout << rbuffer[i] << " ";
    }
    cout << endl;
    return 0;

}
