#ifndef RSA_H
#define RSA_H

#include <NTL/ZZ.h>
#include <iostream>
#include "AlgFunc.h"
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace NTL;
using namespace std;
using namespace AAbs;

const long BITS = 1024;


class RSA
{
    public:
        ZZ PublicKey[2];
        RSA();
        void Display();
        void RSA_Program();

    private:
        ZZ PrivateKey, N, $N, P, Q, ZZimage;

        ZZ* Generator();
        void SaveKeys();
        void ReaderOfImage();
        void ImageCypher(ZZ&);
        void ImageDCypher(ZZ&);
        string Cryptor(string,ZZ,ZZ);
        string Decryptor(string,ZZ,ZZ);

        void ALPH_Normalization(string&,string&);
        void ASCII_Normalization(string&,string&);

        void getEm();
        void getRe();

        ZZ KEYS[5];

        fstream crypted, decrypted, publkey, privkey, image;
        HANDLE hConsole;
        string op, imageS, rute;
};

#endif // RSA_H
