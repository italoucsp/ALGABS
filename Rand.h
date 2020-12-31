#ifndef RAND_H
#define RAND_H

#include <iostream>
#include <bitset>
#include <vector>
#include <windows.h>
#include <winuser.h>
#include <sstream>
#include <time.h>
#include <NTL/ZZ.h>
#include <string>

const char Charge = static_cast<char>(177);
using namespace std;
using namespace NTL;
typedef unsigned short int usi;

void gotoxy(int , int );
inline string hexToBin(string);
inline string genSubKeys(bitset<64>, int);
inline void circularShiftLeft(bitset<28>&, usi);
inline bitset<64> convertirZZaBits(ZZ numero);
inline ZZ randomNum(ZZ seed=ZZ(1));
inline ZZ randNumGenDES(long num);
int currentDateTime();
float cuadrados_medios(int);
ZZ MOD(ZZ, ZZ);
ZZ MOD(ZZ, int);
ZZ INV(ZZ, ZZ);
ZZ ExMOD(ZZ, ZZ, ZZ);
ZZ genRandNumber(long);
ZZ genPrimeNew(long);
bool Miller(ZZ &, long = 10);
inline int mod(int ,int );
//string PCname = GetComputerName();

#endif // RAND_H
