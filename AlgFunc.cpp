#include "AlgFunc.h"

namespace AAbs {
    ZZ GenByDES(long bits){
        ZZ limit = ZZ(1), number;
        limit <<= bits;
        number = Mod(sqr(Random()),limit);
        string SNUM;
        bitset<1024> NUMZZ;
        for(long b = 0; b < bits; b++){
            NUMZZ.set(b,bit(number,b));
        }
        DES Generator(NUMZZ);
        Generator.genSubKeys();
        for(int i = 0; i < 22; i++){
            SNUM += Generator.subkeys[i];
        }
        ZZ num = BINtoZZ(SNUM,bits);
        limit >>= 1;
        if(num < limit)num = limit + ZZ(rand());
        if(Mod(num,ZZ(2)) == 0)num -= 1;
        while(!Miller(num)){
            num+=2;
        }
        return num;
    }

    ZZ BINtoZZ(string &NUM, long bits){
        ZZ RES;
        for(int i = bits - 1; i >= 0; i--){
            ZZ BIT = (NUM[i] == '0')?ZZ(0):ZZ(1);
            BIT <<= (i + 1);
            RES += BIT;
        }
        return RES;
    }

    ZZ RestoChino(ZZ &PrivateKey, ZZ &Block, ZZ &p, ZZ &q){
        return Mod(ExpMOD(Block,Mod(PrivateKey,p-1),p)*q*InvEx(q,p)+ExpMOD(Block,Mod(PrivateKey,q-1),q)*p*InvEx(p,q),p*q);
    }

    bool Miller(ZZ &num, long loops){
        if(Mod(num,ZZ(2)) == 0) return false;
        if((Mod(num,ZZ(6)) != 1 || Mod(num,ZZ(6)) != 5) && Mod(num,ZZ(5)) == 0) return false;
        ZZ d = num - ZZ(1);
        while (Mod(d,ZZ(2)) == ZZ(0)){
             d >>= 1;
        }
        for(long i = 0; i < loops; i++){
            ZZ a = Mod(Random(),num - 4) + 2;
            ZZ temp = d;
            ZZ x = ExpMOD(a,temp,num);
            while (temp != num - ZZ(1) && x != ZZ(1) && x != num - ZZ(1)){
                x = ExpMOD(x,ZZ(2),num);
                temp <<= 1;
            }
            if (x != num - ZZ(1) && Mod(temp,ZZ(2)) == ZZ(0)){
                return false;
            }
        }
        return true;
    }

    ZZ PrimeSet(long bits, long loops){
        ZZ pnum = RandomBits_ZZ(bits);
        pnum = (Mod(pnum,ZZ(2)) == 0)?(pnum + ZZ(1)):pnum;
        for(; Miller(pnum,loops) == 0; pnum += 2){ }
        return pnum;
    }
    ZZ Pollard(ZZ n){
        ZZ x = ZZ(2), y = ZZ(2), d = ZZ(1);
        while(d == ZZ(1)){
            x = Pollard(x);
            y = Pollard(Pollard(y));
            d = MCD((x-y), n);
            if(d == n) return ZZ(0);
            else return d;
        }
    }
    bool Solovay(ZZ n, long bit, int k){
        for(int j = 0; j < k; j++){
            ZZ a = Mod(Random(bit),n - ZZ(4)) + ZZ(2);///número aleatorio en un intervalo de [2,n-2]
            ZZ r = ExpMOD(a,(n-ZZ(1))/ZZ(2),n);
            if(r != ZZ(1) && r != n - ZZ(1))
                return false;
            long s = Jacobi(a,n);
            if(r != Mod(ZZ(s),n))
                return false;
        }
        return true;
    }

    bool Modular_Prime_Test(ZZ &n){
        if(n > 1){
            if(n == 2 || n == 3 || n == 5 || n == 7 || n == 11){return true;}
            ZZ mod6 = Mod(n,ZZ(6));
            if((mod6 == ZZ(1) || mod6 == ZZ(5)) && Mod(n,ZZ(5)) != 0){
                if(Mod(n,ZZ(7)) != 0 && Mod(n,ZZ(11)) != 0 && Mod(n*n,ZZ(6)) == 1/* && Mod(SqrRoot(n),ZZ(6)) == 4*/){
                    return true;
                }
            }
        }
        return false;
    }

    ZZ NPrimeRandom(long &Nbits){
        ZZ n = RandomBits_ZZ(Nbits);
        if(Mod(n,ZZ(2))==0) n = n - ZZ(1);
        while(/*ProbPrime(n) == 0*/IsPrime(n) == 0){
            n = RandomBits_ZZ(Nbits);
            if(Mod(n,ZZ(2))==0) n = n - ZZ(1);
        }
        return n;
    }

	ZZ Mod(ZZ num, ZZ mod) {
		ZZ r = (num < 0) ? (num - ((num / mod) - 1)*mod) : num - (num / mod)*mod;
		return r;
	}

	int Mod(int num, int mod) {
		int r = (num < 0) ? (num - ((num / mod) - 1)*mod) : num - (num / mod)*mod;
		return r;
	}

	ZZ Mod(ZZ num, int mod) {
		ZZ r = (num < 0) ? (num - ((num / mod) - 1)*mod) : num - (num / mod)*mod;
		return r;
	}

	void SWAP(ZZ &a, ZZ &b) {
		ZZ temp = a;
		a = b;
		b = temp;
	}

	bool IsPrime(ZZ &Number){
	    /*if (Mod(Number,11) == 0 || Mod(Number,13) == 0)
            return false;*/
        if (Mod(Number,6) != 1 && Mod(Number,6) != 5)
            return false;
        ZZ r = SqrRoot(Number);
        ZZ i = ZZ(1);
        while (6*i-1 <= r){
            if (Mod(Number,(6*i-1)) == ZZ(0))
                return false;
            if (Mod(Number,(6*i+1)) == ZZ(0))
                return false;
            i = i + 1;
            return true;
        }
        return false;
	}

	bool IsPrimeB(ZZ &Number, long &bits){
	    if(Mod(Number,2)==0)return false;
	    if(Mod(Number,3)==0)return false;
	    if(Mod(Number,5)==0)return false;
	    if(Mod(Number,7)==0)return false;
	    ZZ sqrn = SqrRoot(Number);
	    while(sqrn != 1){
            if(Mod(Number,sqrn)==0)return false;
            sqrn = SqrRoot(sqrn);
	    }
	    return true;
	}

	bool IsPrime(int &Number){
        if (Mod(Number,6) != 1 && Mod(Number,6) != 5)
            return false;
        int r = sqrt(Number);
        int i = 1;
        while (6*i-1 <= r){
            if (Mod(Number,(6*i-1)) == 0)
                return false;
            if (Mod(Number,(6*i+1)) == 0)
                return false;
            i = i + 1;
            return true;
        }
        return false;
	}

	ZZ MCD(ZZ m, ZZ n) {
		ZZ temp = m;
		if (m == ZZ(0) or n == ZZ(0))return ZZ(0);
		int s = 0;
		while (Mod(m, 2) == ZZ(0) and Mod(n, 2) == ZZ(0)) {
			m >>= 1;
			n >>= 1;
			s++;
		}
		while (Mod(n, 2) == ZZ(0)) {
			n >>= 1;
		}
		while (m != 0) {
			while (Mod(m, 2) == ZZ(0)) {
				m >>= 1;
			}
			if (m < n) SWAP(m, n);
			m -= n;
			m >>= 1;
			if (m == temp) m = ZZ(0);
		}
		return (pow(2, s)*n);
	}

	ZZ Inv(ZZ n, ZZ m) {
		ZZ i = ZZ(1);
		if (n > m) { n = Mod(n, m) + m; i = m; }
		ZZ p = m * i + 1;
		while (Mod(p, n) != 0) {
			i++;
			p = m * i + 1;
		}
		ZZ result = p / n;
		if (result > m) { result -= m; }
		return result;
	}

	ZZ* EuEx(ZZ n1, ZZ n2){
		ZZ x2 = ZZ(1), x1 = ZZ(0), y2 = ZZ(0), y1 = ZZ(1), q, x, y, z, Invs = ZZ(1), sav = n2;
		if (n2 == ZZ(0)) {
			ZZ arr[4] = { n1, x2, y2, y1 };
			return arr;
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
			ZZ arr[4] = { n1, x2, y2, Invs };
			return arr;
		}
	}

	ZZ InvEx(ZZ n1, ZZ n2){
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

	ZZ ExpMOD(ZZ B, ZZ Exp, ZZ M) {
		ZZ Result = ZZ(1), ExpTemp = ZZ(1), EV = ZZ(1);
		bool Init = true;
		while (Exp != ZZ(0)) {
			ExpTemp = Mod(EV*EV, M);
			if (Init == true) { ExpTemp = B; }
			if (Mod(Exp, 2) == 1) {
				Result = Mod(ExpTemp * Result,M);
			}
			EV = ExpTemp;
			Exp /= 2;
			Init = false;
		}
		return Result;
	}
	int ToInt(string l){
	    if(l[0] == "0"[0]){
            return 0;
	    }
	    if(l[0] == "1"[0]){
            return 1;
	    }
	    if(l[0] == "2"[0]){
            return 2;
	    }
	    if(l[0] == "3"[0]){
            return 3;
	    }
	    if(l[0] == "4"[0]){
            return 4;
	    }
	    if(l[0] == "5"[0]){
            return 5;
	    }
	    if(l[0] == "6"[0]){
            return 6;
	    }
	    if(l[0] == "7"[0]){
            return 7;
	    }
	    if(l[0] == "8"[0]){
            return 8;
	    }
	    if(l[0] == "9"[0]){
            return 9;
	    }
	}
}
