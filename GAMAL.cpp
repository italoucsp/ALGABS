#include "GAMAL.h"

GAMAL::GAMAL(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    cout << "****************<EL GAMAL>*******************" << endl;
}

void GAMAL::PROGRAM(){
    Key_Generator();
}

ZZ Phi(ZZ &n){
    if(Miller(n) != false){
        return n - 1;
    }

}

void GAMAL::Key_Generator(){

    cout << "\n->CREANDO LLAVES [----------------";
    gotoxy(34,2); cout << "]"; gotoxy(18,2);
    ZZ q = genPrimeNew(BITS);
    p = 2*q + 1;
    while(Miller(p) == 0){
       q = genPrimeNew(BITS);
       p = 2*q + 1;
    }
    cout << Charge << Charge;
    P1 = genPrimeNew(BITS/2);
    cout << Charge << Charge;
    P2 = genPrimeNew(BITS/2);
    cout << Charge << Charge;
    N = P1 * P2;
    cout << Charge << Charge;
    Phi_N = (P1 - ZZ(1))*(P2 - ZZ(1));
    cout << Charge << Charge;
    d = SelectFromGroup(p,2);
    cout << Charge << Charge;
    e1 = SelectFromGroup(p,3);
    cout << Charge << Charge;
    e2 = ExMOD(e1,d,p);
    cout << Charge << Charge;
    cout << "]" << endl;
    SetConsoleTextAttribute(hConsole, 6);
    cout << "->PUBLIC_KEY: " << endl;
    cout << "\t" << "e1: " << e1 << endl;
    cout << "\t" << "e2: " << e2 << endl;
    cout << "\t" << "p: " << p << endl;
    cout << "->PRIVATE_KEY: " << d << endl;
    SetConsoleTextAttribute(hConsole, 2);
    Writer.open("KEYS/MyKeys.txt", ios::out);
    Writer << "->PUBLIC_KEY: " << endl;
    Writer << "\t" << "e1: " << e1 << endl;
    Writer << "\t" << "e2: " << e2 << endl;
    Writer << "\t" << "p: " << p << endl;
    Writer.close();
    Writer.open("KEYS/PUK/E1.txt", ios::out);
    Writer << e1;
    Writer.close();
    Writer.open("KEYS/PUK/E2.txt", ios::out);
    Writer << e2;
    Writer.close();
    Writer.open("KEYS/PUK/P.txt", ios::out);
    Writer << p;
    Writer.close();
    Writer.open("KEYS/PRIV/D.txt", ios::out);
    Writer << d;
    Writer.close();
    cout << "\n->Claves guardadas !!!" << endl;
}

ZZ GAMAL::SelectFromGroup(ZZ &p, int op){
    ZZ num, limit = ZZ(2);
    limit <<= BITS;
    if(op == 1){
        num = MOD(genRandNumber(BITS),p-limit-1) + limit/2+1;
        return num;
    }
    else if(op == 2){
        num = MOD(genRandNumber(BITS),p-limit-3) + limit/2+1;
        return num;
    }
    else if(op == 3){
        bool found = true;
        while(found){
            num = MOD(genRandNumber(BITS),p-limit-1) + limit/2+1;
            if(MOD(num*num,p) != 1 && ExMOD(num,(p-1)/2,p) != 1){
                found = false;
            }
        }
        return num;
    }
}

void GAMAL::GAMAL_Cypher(){
    system("cls");
    cout << "CYPHER" << endl;
    cout << "->Nombre del Archivo: "; cin >> route;
    string E1,E2,PK;
    Reader.open("MENSAJES/"+route+".txt", ios::in);
    if(Reader.is_open()){
        while(!Reader.eof()){
            string line;
            getline(Reader,line);
            P += line;
        }
    }
    Reader.close();
    Reader.open("KEYS/E1.txt", ios::in);
    if(Reader.is_open()){
        while(!Reader.eof()){
            string line;
            getline(Reader,line);
            E1 += line;
        }
    }
    Reader.close();
    Reader.open("KEYS/E2.txt", ios::in);
    if(Reader.is_open()){
        while(!Reader.eof()){
            string line;
            getline(Reader,line);
            E2 += line;
        }
    }
    Reader.close();
    Reader.open("KEYS/P.txt", ios::in);
    if(Reader.is_open()){
        while(!Reader.eof()){
            string line;
            getline(Reader,line);
            PK += line;
        }
    }
    Reader.close();
    ZZ KEY_E1(INIT_VAL, E1.c_str());
    ZZ KEY_E2(INIT_VAL, E2.c_str());
    ZZ KEY_P(INIT_VAL, PK.c_str());
    ZZ C1,C2,R = SelectFromGroup(KEY_P);
    C1 = ExMOD(KEY_E1,R,KEY_P);
    for(int i = 0; i < P.length(); i++){
        C2 = ExMOD(KEY_E2,R,KEY_P);
    }

}

void GAMAL::GAMAL_Decypher(){

}

ZZ GAMAL::Rubrica(ZZ &d, ZZ &N, string &s){
    stringstream N1;
    N1 << N;
    long int bloq = N1.str().length() - 1;
    string aux;
    string res;
    string aux2;
    string ceros;
    for(int cont = 0; cont < s.length(); cont += bloq){
        ceros = "0";
        aux = s.substr(cont, bloq);
        while(aux.length() < bloq){
            aux += "0";
        }
        ZZ sn(NTL::INIT_VAL,aux.c_str());
        ZZ ns = ExMOD(sn,d,N);
        stringstream N2;
        N2 << ns;
        aux2 = N2.str();
        while(aux2.length() < bloq + 1){
            aux2 = ceros + aux2;
            ceros += "0";
        }
        res += aux2;
    }
    return d;

}
ZZ GAMAL::DRubrica(ZZ &es, ZZ &Ns, string &s){
    stringstream N1;
    N1 << Ns;
    long int bloq = N1.str().length() - 1;
    string aux;
    string res = "";
    string aux2;
    string ceros;
    for(int cont = s.length() - bloq; cont > -bloq; cont -= bloq){
        ceros = "0";
        aux = s.substr(cont, bloq);
        while(aux.length() < bloq){
            aux += "0";
        }
        ZZ sn(NTL::INIT_VAL,aux.c_str());
        ZZ ns = ExMOD(sn,es,Ns);
        stringstream N2;
        N2 << ns;
        aux2 = N2.str();
        while(aux2.length() < bloq + 1){
            aux2 = ceros + aux2;
            ceros += "0";
        }
        res = aux2 + res;
    }
    return d;
}

ZZ GAMAL::DURubrica(ZZ &ds, ZZ &Ns, string &s){
    stringstream N1;
    N1 << Ns;
    long int bloq = N1.str().length();
    string aux;
    string res;
    string aux2;
    string ceros;
    for(int cont = 0; cont < s.length(); cont += bloq)
    {
        ceros = "0";
        aux = s.substr(cont, bloq);
        ZZ sn(NTL::INIT_VAL,aux.c_str());
        ZZ ns = ExMOD(sn,ds,Ns);
        stringstream N2;
        N2 << ns;
        aux2 = N2.str();
        while(aux2.length() < bloq - 1){
            aux2 = ceros + aux2;
            ceros += "0";
        }
        res += aux2;
    }
    return d;

}

void GAMAL::ReaderOfImage(){
    cout << "Ruta de la Firma: "; cin >> rute;
    cin.get();
    image.open("PPM/"+rute+".ppm", ios::in);
	string files,tamx,tamy,R,G,B;
	if (image.is_open()) {
		while (!image.eof()) {
			string line;
			getline(image,line);
			files += line;
			files.push_back('\n');
		}
	}
	image.close();
	int index = files.find(" ") + 1, findex;
	tamx.assign(files, 3, index - 3);
	tamy.assign(files, index, index - 3);
	int tx = atoi(tamx.c_str()), ty = atoi(tamy.c_str());
	string LINE,T_RGB;
	index = files.find('\n',index + 1);
	index ++;
	index = files.find('\n', index + 1);
	int ibe = 0, ifi;
	for (int y = 0; y < ty; y++) {
		for (int x = 0; x < tx; x++) {
			findex = files.find('\n', index + 1);
			LINE.assign(files,index,findex - index);
			ibe = 0;
			ifi = LINE.find(" ");
			R.assign(LINE,ibe,ifi);
			ibe = ifi + 1;
			ifi = LINE.find(" ",ibe) - ibe;
			G.assign(LINE, ibe, ifi);
			ifi = LINE.find(" ", ibe);
			ibe = ifi + 1;
			ifi = LINE.find('\n', ibe) - ibe;
			B.assign(LINE, ibe, ifi);
            T_RGB = to_string(atoi(R.c_str()));
            if(atoi(R.c_str()) < 100)T_RGB = (atoi(R.c_str()) < 10)?"00"+T_RGB:"0"+T_RGB;
            imageS += T_RGB;
            T_RGB = to_string(atoi(G.c_str()));
            if(atoi(G.c_str()) < 100)T_RGB = (atoi(G.c_str()) < 10)?"00"+T_RGB:"0"+T_RGB;
            imageS += T_RGB;
            T_RGB = to_string(atoi(B.c_str()));
            if(atoi(B.c_str()) < 100)T_RGB = (atoi(B.c_str()) < 10)?"00"+T_RGB:"0"+T_RGB;
			imageS += T_RGB;
			index = findex;
		}
	}
	cout << imageS << endl;
	cout << "->FIRMA LEIDA CON EXITO!!!" << endl;
}

void GAMAL::RebuilderImage(ZZ &DSIGNATURE){
    string ruta; cout << "Ruta de la firma: "; cin >> ruta;
    image.open("MENSAJES/DSIGANTURES/"+ruta+"(GYR).ppm", ios::out);
	stringstream IM;
    IM << DSIGNATURE;
    string IMG = IM.str();
	image << "P3" << endl;
	image << 16 << " " << 16 << endl;
	image << "255" << endl;
	int iter = 0;
	for(int y = 0; y < 16; y++){
        for(int x = 0; x < 16; x++){
            image << IMG.substr(iter,3) << " " << IMG.substr(iter + 3, 3) << " " << IMG.substr(iter + 6, 3) << endl;
            iter += 9;
        }
	}
	image.close();
	cout << "->FIRMA RECONSTRUIDA CON EXITO!!!" << endl;
}

