#include <iostream>
#include "common.h"
#include "rsa.h"

using namespace std;

int main(int argc, char* argv[])
{
    RSA keys;
    keys.generateKey(8, 32);

    cout << "PublicKey is " << keys.getPublicKey().firstNumber << " " << keys.getPublicKey().SecondNumber <<endl;
    cout << "PrivateKey is " << keys.getPrivateKey().firstNumber << " " << keys.getPrivateKey().SecondNumber << endl;

    const int bufSize = 10;
    char* rbuffer = new char[bufSize] {'a', 'b', 'c','a', 'b', 'c','a', 'b', 'c', 'a'};

    for(int i = 0; i < bufSize; ++i) {
        cout << (int)rbuffer[i] << " ";
    }
    cout << endl;

    keys.encrypt(rbuffer, bufSize);
    for(int i = 0; i < bufSize; ++i) {
        cout << (int)rbuffer[i] << " ";
    }
    cout << endl;

    keys.decrypt(rbuffer, bufSize);
    for(int i = 0; i < bufSize; ++i) {
        cout << (int)rbuffer[i] << " ";
    }
    cout << endl;
    return 0;

}
