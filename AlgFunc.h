#ifndef ALGFUNC_H
#define ALGFUNC_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <NTL/ZZ.h>
#include "RandomNTL_ZZ.h"
#include "DES.h"
#include <sstream>

#define arrsize(arr) sizeof(arr)/sizeof(*arr)
//NTL::ZZ NUM;
//#define ZERO NUM - NUM

using namespace NTL;
using namespace RAND;
using namespace std;

namespace AAbs {
    ZZ BINtoZZ(string&,long);
    ZZ GenByDES(long);
	ZZ Mod(ZZ, ZZ);
	ZZ Pollard(ZZ);
	ZZ PrimeSet(long,long=10);
	bool Miller(ZZ&,long=10);
	ZZ NPrimeRandom(long&);
	bool Modular_Prime_Test(ZZ&);
	ZZ RestoChino(ZZ&,ZZ&,ZZ&,ZZ&);
	bool Solovay(ZZ,long,int=10);
	bool IsPrime(ZZ&);
	bool IsPrimeB(ZZ&,long&);
	bool IsPrime(int&);
	ZZ Mod(ZZ, int);
	int Mod(int, int);
	int ToInt(string);
	void SWAP(ZZ&, ZZ&);
	ZZ* EuEx(ZZ, ZZ);
	ZZ InvEx(ZZ, ZZ);
	ZZ Inv(ZZ, ZZ);
	ZZ MCD(ZZ, ZZ);
	ZZ ExpMOD(ZZ, ZZ, ZZ);
	const string Alf = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
}



#endif // ALGFUNC_H
