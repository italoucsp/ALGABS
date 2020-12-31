#ifndef _RANDNUMGENDES_H
#define _RANDNUMGENDES_H

#include <iostream>
#include <bitset>
#include <vector>
#include <windows.h>
#include <winuser.h>
#include <sstream>
#include <time.h>
#include <NTL/ZZ.h>
#include "AlgFunc.h"

using namespace std;
using namespace NTL;
typedef unsigned short int usi;

inline string hexToBin(string);
inline string genSubKeys(bitset<64>, int);
inline void circularShiftLeft(bitset<28>&, usi);
inline bitset<64> convertirZZaBits(ZZ numero);
inline ZZ randomNum(ZZ seed=ZZ(1));
inline ZZ randNumGenDES(long num);



int currentDateTime() {
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);

    int h = tstruct.tm_hour ;
    h = (h * h) - 1;
    int m = tstruct.tm_min;
    m = (m * m) - 1;
    int s = tstruct.tm_sec;
    s = (s * s) - 1;
    int mo = tstruct.tm_mon + 1;
    mo = (mo * mo) - 1;
    int y = tstruct.tm_year;
    y = (y * y) - 1;
    int d = tstruct.tm_wday;
    d = (d * d) - 1;
    int md = tstruct.tm_mday;
    md = (md * md) - 1;

    int res =  h + m + s + mo + y + d + md;
    return res;

}

float cuadrados_medios(int a) {
    float rres = 0.0,x1, x2;
    string aux;
    x2 = a;

    for(int x = 0;x <= 5; x++)
    {
        if(x2 < 1000){x1 = (x2 * x2) - 500;}
        else{x1 = x2;}

        std::stringstream res;
        res << x1;
        aux = res.str();

        if(aux.length() <= 4){aux = aux.substr(aux.length() - 3,3);}
        else{aux = aux.substr(aux.length() - 4,3);}

        std::istringstream is (aux);
        is >> x2;
        rres += x2;

    }
    return rres;
}


ZZ MOD(ZZ num, ZZ mod) {
    ZZ r = (num < 0) ? (num - ((num / mod) - 1)*mod) : num - (num / mod)*mod;
    return r;
}

ZZ MOD(ZZ num, int mod) {
    ZZ r = (num < 0) ? (num - ((num / mod) - 1)*mod) : num - (num / mod)*mod;
    return r;
}

ZZ INV(ZZ n1, ZZ n2){
		ZZ x2 = ZZ(1), x1 = ZZ(0), y2 = ZZ(0), y1 = ZZ(1), q, x, y, z, Invs = ZZ(1), sav = n2;
		if (n2 == ZZ(0)) {
			return Invs;
		}
		else {
			while (n2 > ZZ(0)) {
				q = n1 / n2;
                x = n1; y = x2; z = y2;
				n1 = n2; n2 = x - q * n2;
				x2 = x1; x1 = y - q * x1;
				y2 = y1; y1 = z - q * y1;
				if (n2 == ZZ(1)) {
					Invs = x1;
					if (Invs < ZZ(0)) {
						Invs = sav + Invs;
					}
				}
			}
			return Invs;
		}
	}

ZZ ExMOD(ZZ B, ZZ Exp, ZZ M) {
    ZZ Result = ZZ(1), ExpTemp = ZZ(1), EV = ZZ(1);
    bool Init = true;
    while (Exp != ZZ(0)) {
        ExpTemp = MOD(EV*EV, M);
        if (Init == true) { ExpTemp = B; }
        if (MOD(Exp, 2) == 1) {
            Result = MOD(ExpTemp * Result,M);
        }
        EV = ExpTemp;
        Exp /= 2;
        Init = false;
    }
    return Result;
}

ZZ genRandNumber(long);

/*bool Miller(ZZ &num, long loops = 10){
        if(MOD(num,ZZ(2)) == 0) return false;
        if((MOD(num,ZZ(6)) != 1 || MOD(num,ZZ(6)) != 5) && MOD(num,ZZ(5)) == 0) return false;
        ZZ d = num - ZZ(1);
        while (MOD(d,ZZ(2)) == ZZ(0)){
             d >>= 1;
        }
        for(long i = 0; i < loops; i++){
            ZZ a = MOD(genRandNumber(1024),num - 4) + 2;
            ZZ temp = d;
            ZZ x = ExMOD(a,temp,num);
            while (temp != num - ZZ(1) && x != ZZ(1) && x != num - ZZ(1)){
                x = ExMOD(x,ZZ(2),num);
                temp <<= 1;
            }
            if (x != num - ZZ(1) && MOD(temp,ZZ(2)) == ZZ(0)){
                return false;
            }
        }
        return true;
    }*/


ZZ convBitstoZZ(string bitsStr){
    ZZ conversion;
    for(int i=bitsStr.size();i>=0;i--){
        if(bitsStr[i] == '1'){conversion += power2_ZZ(i);}
    }
    return conversion;

}

inline int mod(int dividiendo,int divisor){
    int cociente;
    int residuo;
    cociente = dividiendo / divisor;
    residuo = dividiendo - (cociente*divisor);
    if(residuo < 0){
        residuo += divisor;
    }
    return residuo;
}

inline bitset<64> convertirZZaBits(ZZ numero) {
    string bitsZZ;
    long tam = NumBits(numero);
    for(int i = 0; i<tam;i++){
        string temp;
        stringstream strstream;
        strstream << bit(numero,i);
        strstream >> temp;
        bitsZZ += temp ;
    }
  bitset<64> _k(bitsZZ);
  return _k;
}

inline ZZ randomNum(ZZ seed){
    unsigned t0, t1;
    t0=clock();

    int x,y, segundos, numeroN,actualT;
    long res;
    time_t seconds1,seconds2;
    double timeN;

    seconds1 = time(NULL);
	segundos += int(seconds1);
    Sleep(5);
    actualT = currentDateTime();
    POINT cursor; GetCursorPos(&cursor);
    x=cursor.x; y=cursor.y;
    t1 = clock();
    res = cuadrados_medios((x*y) * actualT);
    seconds2 = time(NULL);
	segundos += int(seconds2);
    timeN = (double(t1-t0)/CLOCKS_PER_SEC);
    numeroN = int(timeN*1000);


    return abs((ZZ(segundos*(x+y+res)+ seed + (y*x*res)+(segundos*numeroN*res))*seed));
}

inline ZZ randSeed(long num){
    ZZ numero = randomNum();
    for(int i=0;i<10;i++){
        numero = randomNum(numero);
    }
    ZZ topeInf= power2_ZZ(num)/conv<ZZ>(2);
    ZZ topeSup= power2_ZZ(num)-conv<ZZ>(1);

    return topeInf + numero % topeSup;
}

inline string hexToBin(string hex) {
  string binary;
  for (usi i = 0; i < hex.size(); i++) {
    string digit;

    if (hex[i] >= '0' && hex[i] <= '9') {
      usi dec = hex[i]-'0';
      while (dec > 0) {
        digit += (dec%2 + '0'); // 1 or 0
        dec /= 2;
      }
      while (digit.size() < 4) digit += '0';
      for (short int j = 3; j >= 0; j--)
        binary += digit[j];
    }

    else {
      usi dec = hex[i]-'A'+10;
      while (dec > 0) {
        digit += (dec%2 + '0'); // 1 or 0
        dec /= 2;
      }
      for (short int j = 3; j >= 0; j--)
        binary += digit[j];
    }
  }

  return binary;
}

inline string genSubKeys(bitset<64> key, int bits) {
  usi perm1[56] = {57, 49, 41, 33, 25, 17,  9,
                    1, 58, 50, 42, 34, 26, 18,
                  10,  2, 59, 51, 43, 35, 27,
                  19, 11,  3, 60, 52, 44, 36,
                  63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                  14,  6, 61, 53, 45, 37, 29,
                  21, 13,  5, 28, 20, 12,  4};
  usi perm2[48] = {14, 17, 11, 24,  1,  5,
                    3, 28, 15,  6, 21, 10,
                  23, 19, 12,  5, 26,  8,
                  16,  7, 27, 20, 13,  2,
                  41, 52, 31, 37, 47, 55,
                  30, 40, 51, 45, 33, 48,
                  44, 49, 39, 56, 34, 53,
                  46, 42, 50, 36, 29, 32};
  usi shifts[16] = {1, 1, 2, 2,
                    2, 2, 2, 2,
                    1, 2, 2, 2,
                    2, 2, 2, 1};
  vector<string> subkeys;
  bitset<56> _k;
  for (usi i = 0; i < 56; i++)
    _k.set(55-i, key[64-perm1[i]]);

  int necessaryBits = bits/48;
  for (usi i = 0; i < necessaryBits+1; i++) {
    bitset<28> _kLeft(_k.to_string().substr(0, 28));
    bitset<28> _kRight(_k.to_string().substr(28));

    circularShiftLeft(_kLeft, shifts[mod(i, (usi)16)]);
    circularShiftLeft(_kRight, shifts[mod(i, (usi)16)]);

    _k = bitset<56>(_kLeft.to_string() + _kRight.to_string());

    // Permutation Choice 2
    bitset<48> _subkey;
    for (usi i = 0; i < 48; i++)
      _subkey.set(47-i, _k[56-perm2[i]]);
    subkeys.push_back(_subkey.to_string());
  }

  string res;
  for (usi i = 0; i < subkeys.size(); i++)
    res += subkeys[i];

  return res.substr(0, bits);
}

inline void circularShiftLeft(bitset<28> &bset, usi moves) {
  if (moves == 1) {
    bitset<1> MSB = bset.test(27);
    bset <<= moves;
    bset[0] = MSB[0];
  }
  else {
    bitset<2> MSB(bset.to_string().substr(0,2));
    bset <<= moves;
    bset[0] = MSB[0];
    bset[1] = MSB[1];
  }
}

ZZ genRandNumber(long n){
	string val = genSubKeys(convertirZZaBits(randSeed(n)),n);
	ZZ cont = convBitstoZZ(val);
	return cont;
}

ZZ genPrimeNew(long n){
    string val = genSubKeys(convertirZZaBits(randSeed(n)),n);
    ZZ cont = convBitstoZZ(val);
    if(MOD(cont,2) == 0){cont += 1;}
    while(!Miller(cont)){
            cont+=2;
    }
    return cont;
}


#endif // _RANDNUMGENDES_H
