#include "RSA.h"

RSA::RSA(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
    cout << "GENERAR LLAVES?: "; cin >> op;
	if(op == "si") {
        cout << "->PC: Espere un momento mientras se generan sus claves...\n";
        Generator(); system("cls");
        Display(); SaveKeys(); system("pause"); exit (EXIT_FAILURE);
    }
}

void RSA::SaveKeys(){
    publkey.open("MENSAJES/MYKEYS/MYKEYS_RSA.txt", ios::out);
    publkey << "***PUBLIC KEYS:\n";
	publkey << "->KEY E: " << KEYS[0] << "\n";
	publkey << "->KEY N: " << KEYS[1] << "\n";
	//publkey << "N ->NUM P: " << KEYS[3] << "\n";
	//publkey << "N ->NUM Q: " << KEYS[4] << "\n";
	publkey.close();
	publkey.open("MENSAJES/KEYS/KEY_E.txt", ios::out);
	publkey << KEYS[0];
	publkey.close();
	publkey.open("MENSAJES/KEYS/KEY_N.txt", ios::out);
	publkey << KEYS[1];
	publkey.close();
	publkey.open("MENSAJES/KEYS/PQ/P.txt", ios::out);
	publkey << KEYS[3];
	publkey.close();
	publkey.open("MENSAJES/KEYS/PQ/Q.txt", ios::out);
	publkey << KEYS[4];
	publkey.close();
	privkey.open("MENSAJES/PRIVATEKEY/MYN.txt", ios::out);
	privkey << KEYS[1];
	privkey.close();
	privkey.open("MENSAJES/PRIVATEKEY/PRIVATE.txt", ios::out);
	privkey << KEYS[2];
	privkey.close();
	cout << "->LAS LLAVES HAN SIDO GUARDADAS...!! :)\n";
}

void RSA::RSA_Program(){
    getEm();
    system("cls");
    getRe();
}

void RSA::getEm(){
    cout << "-> EMISOR:\n";
    string PText, Route;
    string PUBL, NK;
    cout << endl;
    cout << "->LLAMADA A PUBLIC KEY!!!" << endl;
    publkey.open("MENSAJES/KEYS/KEY_E.txt", ios::in);
	if (publkey.is_open()) {
		while (!publkey.eof()) {
			string Line;
			getline(publkey, Line);
			PUBL += Line;
		}
	}
	publkey.close();
	ZZ RPUKEY(INIT_VAL, PUBL.c_str());
	cout << "->LLAMADA A N KEY!!!" << endl;
    publkey.open("MENSAJES/KEYS/KEY_N.txt", ios::in);
	if (publkey.is_open()) {
		while (!publkey.eof()) {
			string Line;
			getline(publkey, Line);
			NK += Line;
		}
	}
	publkey.close();
	ZZ RN(INIT_VAL, NK.c_str());
	cin.get();
	cout << "->Escriba el nombre del archivo: "; getline(cin,Route);
    if(Route == "?")return;
    crypted.open("MENSAJES/" + Route + ".txt", ios::in);
	if (crypted.is_open()) {
		while (!crypted.eof()) {
			string Line;
			getline(crypted, Line);
			PText += Line;
		}
	}
	crypted.close();
    crypted.open("MENSAJES/" + Route + "(E).txt", ios::out);
	crypted << Cryptor(PText,RPUKEY,RN);
	cout << "-> EL MENSAJE HA SIDO ENCRIPTADO CORRECTAMENTE...!!!" << endl;
	crypted.close();
    system("pause");
}

void RSA::getRe(){
    cout << "-> RECEPTOR:\n";
    string CText,Route;
    cout << endl;
    string PRIV,NK;
    cout << "->LLAMADA A PRIVATE KEY!!!" << endl;
    privkey.open("MENSAJES/PRIVATEKEY/PRIVATE.txt", ios::in);
	if (privkey.is_open()) {
		while (!privkey.eof()) {
			string Line;
			getline(privkey, Line);
			PRIV += Line;
		}
	}
	privkey.close();
	ZZ RPRKEY(INIT_VAL, PRIV.c_str());
	cout << "->LLAMADA A N KEY!!!" << endl;
    privkey.open("MENSAJES/PRIVATEKEY/MYN.txt", ios::in);
	if (privkey.is_open()) {
		while (!privkey.eof()) {
			string Line;
			getline(privkey, Line);
			NK += Line;
		}
	}
	privkey.close();
	ZZ RN(INIT_VAL, NK.c_str());
    cout << "->Escriba el nombre del archivo: "; getline(cin,Route);
    if(Route == "?")return;
    decrypted.open("MENSAJES/" + Route + ".txt", ios::in);
	if (decrypted.is_open()) {
		while (!decrypted.eof()) {
			string Line;
			getline(decrypted, Line);
			CText += Line;
		}
	}
	decrypted.close();
    decrypted.open("MENSAJES/" + Route + "(D).txt", ios::out);
	decrypted << Decryptor(CText,RPRKEY,RN);
	cout << "-> EL MENSAJE HA SIDO DESENCRIPTADO CORRECTAMENTE...!!!" << endl;
	decrypted.close();
    system("pause");
}

ZZ* RSA::Generator(){
    srand (time(NULL));
    P = GenByDES(BITS/2);//PrimeSet(512);
    //cout << Modular_Prime_Test(P) << endl;
    cout << "->KEY[p] generada" << endl;
    Q = GenByDES(BITS/2);//PrimeSet(512);
    while(P == Q){
        cout << Q << endl;
        Q = GenByDES(BITS/2);//PrimeSet(512);
    }
    //cout << Modular_Prime_Test(Q) << endl;
    cout << "->KEY[q] generada" << endl;
    KEYS[3] = P;
    KEYS[4] = Q;
    N = P*Q;
    cout << "->KEY[n] generada" << endl;
    $N = (P-1)*(Q-1);
    ZZ E = Mod(GenByDES(BITS)/*;PrimeSet(1024)*/,$N);
    while(MCD(E,$N) != ZZ(1)){
        E = Mod(GenByDES(BITS)/*;PrimeSet(1024)*/,$N);
        cout << "->REINTENTANDO..." << endl;
    }
    cout << "->KEY[e] generada" << endl;
    PublicKey[0] = E; PublicKey[1] = N;
    KEYS[0] = PublicKey[0];
    KEYS[1] = PublicKey[1];
    PrivateKey = InvEx(PublicKey[0],$N);
    cout << "->KEY[d] generada" << endl;
    KEYS[2] = PublicKey[2];
    return KEYS;
}

void RSA::Display(){
    cout << "PUBLIC_KEY(E,N):\nE: " << KEYS[0] << "\n";
    cout << "N: " << KEYS[1] << "\n\n";
    stringstream PRK;
    PRK << KEYS[2];
    string PRIVATE_KEY = PRK.str();
    cout << "PRIVATE_KEY: "; for(int i=0; i<PRIVATE_KEY.length()/6;i++)cout << PRIVATE_KEY[i]; cout << "(...)\n\n";
}

void RSA::ALPH_Normalization(string &P,string &CText){
    for (int i = 0; i < P.length(); i++){
        int cind = Alf.find(P[i]) + 2;
        if(cind < 10){
            CText += "0";
        }
        CText += to_string(cind);
    }
}

void RSA::ASCII_Normalization(string &P,string &CText){
    for (int i = 0; i < P.length(); i++){
        int cind = P[i]*1;
        if(cind < 100) CText += "0";
        CText += to_string(cind);
    }
}

string RSA::Cryptor(string P,ZZ PublicKeyR,ZZ NR){
    string CText;
    stringstream Nstrs;
    Nstrs << NR;
    string Nstr = Nstrs.str();
    vector<ZZ> Bloques;
    if(op != "ascii") ALPH_Normalization(P,CText);
    else ASCII_Normalization(P,CText);
    string Compa;
    int increment;
    if(op != "ascii"){
        if(Mod(Nstr.length(),2) == 0){
            for(int pos = 0; pos < CText.length(); pos += increment){
                increment = Nstr.length();
                Compa.assign(CText,pos,increment);
                ZZ BNum(INIT_VAL, Compa.c_str());
                if(BNum >= NR){
                    increment -= 2;
                    Compa.assign(CText,pos,increment);
                    ZZ BNumt(INIT_VAL, Compa.c_str());
                    Bloques.push_back(BNumt);
                }
                else{
                    Bloques.push_back(BNum);
                }
            }
        }
        else{
            for(int pos = 0; pos < CText.length(); pos += increment){
                increment = Nstr.length()-1;
                Compa.assign(CText,pos,increment);
                ZZ BNum(INIT_VAL, Compa.c_str());
                Bloques.push_back(BNum);
            }
        }
    }
    else{
        if(Mod(Nstr.length(),3) == 0){
            for(int pos = 0; pos < CText.length(); pos += increment){
                increment = Nstr.length();
                Compa.assign(CText,pos,increment);
                ZZ BNum(INIT_VAL, Compa.c_str());
                if(BNum >= NR){
                    increment -= 3;
                    Compa.assign(CText,pos,increment);
                    ZZ BNumt(INIT_VAL, Compa.c_str());
                    Bloques.push_back(BNumt);
                }
                else{
                    Bloques.push_back(BNum);
                }
            }
        }
        else{
            for(int pos = 0; pos < CText.length(); pos += increment){
                increment = Nstr.length()-1;
                while(Mod(increment,3) != 0){
                    increment--;
                }
                Compa.assign(CText,pos,increment);
                ZZ BNum(INIT_VAL, Compa.c_str());
                Bloques.push_back(BNum);
            }
        }
    }
    ZZ CNum;
    string CYPHER;
    for(int i = 0; i < Bloques.size(); i++){
        CNum = ExpMOD(Bloques[i],PublicKeyR,NR);
        stringstream CADCb;
        CADCb << CNum;
        string CADCCb = CADCb.str();
        if(CADCCb.length() != Nstr.length()){
            string Inc;
            CADCCb = Inc.assign(Nstr.length() - CADCCb.length(),'0') + CADCCb;
        }
        CYPHER += CADCCb;
    }
    ReaderOfImage();
    ImageCypher(NR);
    return CYPHER;
}

string RSA::Decryptor(string CNum, ZZ PrivateKeyR,ZZ NR){
    string PText;
    stringstream Nstrs;
    Nstrs << NR;
    string Nstr = Nstrs.str();
    string Temp;
    string CTD;
    for(int i = 0,ind = 1; i < CNum.length(); i+=Nstr.length(), ind++){
        Temp.assign(CNum,i,Nstr.length());
        ZZ Numtb(INIT_VAL, Temp.c_str());
        string PS,QS;
        privkey.open("MENSAJES/KEYS/PQ/P.txt", ios::in);
        if (privkey.is_open()) {
            while (!privkey.eof()) {
                string Line;
                getline(privkey, Line);
                PS += Line;
            }
        }
        privkey.close();
        ZZ P(INIT_VAL, PS.c_str());
        privkey.open("MENSAJES/KEYS/PQ/Q.txt", ios::in);
        if (privkey.is_open()) {
            while (!privkey.eof()) {
                string Line;
                getline(privkey, Line);
                QS += Line;
            }
        }
        privkey.close();
        ZZ Q(INIT_VAL, QS.c_str());

        Numtb = RestoChino(PrivateKeyR, Numtb,P,Q);
        stringstream DCTF;
        DCTF << Numtb;
        string DCTFF = DCTF.str();
        if(op != "ascii"){
            if(Mod(DCTFF.length(),2) != 0){
                DCTFF = "0" + DCTFF;
            }
        }
        if(op == "ascii"){
            if(Mod(DCTFF.length(),3) != 0){
                DCTFF = "0" + DCTFF;
            }
        }
        CTD += DCTFF;
    }
    if(op == "ascii") {
        for(int i = 0; i < CTD.length(); i += 3){
            string c1 = {CTD[i],'\0'},c2 = {CTD[i+1],'\0'},c3 = {CTD[i+2],'\0'};
            int ind = ToInt(c1)*100 + ToInt(c2)*10 + ToInt(c3);
            PText.push_back(static_cast<char>(ind));
        }
    }
    else{
        for(int i = 0; i < CTD.length(); i += 2){
            string c1 = {CTD[i],'\0'},c2 = {CTD[i+1],'\0'};
            int ind = ToInt(c1)*10 + ToInt(c2);
            PText += Alf[ind-2];
        }
    }
    ImageDCypher(NR);
    return PText;
}

void RSA::ReaderOfImage(){
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
			//imageS += " ";
			index = findex;
		}
	}
	ZZ ZZi(INIT_VAL, imageS.c_str());
	ZZimage = ZZi;
	//cout << ZZimage << endl;
	cout << "->FIRMA LEIDA CON EXITO!!!" << endl;
}

void RSA::ImageCypher(ZZ &NR){
    string PRIV;
    privkey.open("MENSAJES/PRIVATEKEY/PRIVATE.txt", ios::in);
	if (privkey.is_open()) {
		while (!privkey.eof()) {
			string Line;
			getline(privkey, Line);
			PRIV += Line;
		}
	}
	privkey.close();
	ZZ RPRKEY(INIT_VAL, PRIV.c_str());
    ZZimage = ExpMOD(ZZimage,RPRKEY,ZZimage+ZZ(1));
    image.open("MENSAJES/SIGNATURES/"+rute+".txt",ios::out);
    image << ZZimage;
    image.close();
    cout << "->FIRMA CIFRADA CON EXITO!!!" << endl;
}

void RSA::ImageDCypher(ZZ &NR){
    string PUBL;
    publkey.open("MENSAJES/KEYS/KEY_E.txt", ios::in);
	if (publkey.is_open()) {
		while (!publkey.eof()) {
			string Line;
			getline(publkey, Line);
			PUBL += Line;
		}
	}
	publkey.close();
	string ruta, numb; cout << "->RUTA de la firma cifrada: "; cin >> ruta; cin.get();
	ifstream signature("MENSAJES/SIGNATURES/"+ruta+".txt");
	if (signature.is_open()) {
		while (!signature.eof()) {
			string Line;
			getline(signature, Line);
			numb += Line;
		}
	}
	signature.close();
	ZZ NUMB(INIT_VAL, numb.c_str());
	ZZ RPUKEY(INIT_VAL, PUBL.c_str());
	ZZ DSIGNATURE = ExpMOD(NUMB,RPUKEY,NUMB + 1);
	//cout << DSIGNATURE << endl;
	image.open("MENSAJES/DSIGANTURES/"+ruta+"(RSA).ppm", ios::out);
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
	cout << "->FIRMA DESCIFRADA CON EXITO!!!" << endl;
}
