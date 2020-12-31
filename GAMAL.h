#ifndef GAMAL_H
#define GAMAL_H
#include "Rand.h"
#include <fstream>

using namespace NTL;

const long BITS = 64;

struct GAMAL
{
    GAMAL();
    void PROGRAM();


    void Key_Generator();
    void GAMAL_Cypher();
    void GAMAL_Decypher();
    ZZ SelectFromGroup(ZZ&,int=1);

    void ReaderOfImage();
    void RebuilderImage(ZZ&);
    ZZ DURubrica(ZZ&, ZZ&, string&);
    ZZ DRubrica(ZZ&, ZZ&, string&);
    ZZ Rubrica(ZZ&, ZZ&, string&);

    string P, route, rute, imageS;
    ZZ p, d, e1, e2, P1, P2, N, Phi_N;
    fstream Reader, Writer, image;
    HANDLE  hConsole;
};

#endif // GAMAL_H
