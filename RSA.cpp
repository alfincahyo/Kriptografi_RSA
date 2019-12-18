#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

int p, q, n, r, e, d;
bool isPrime(int);
bool areCoprime(int, int);
string trim(string);
string intToBinary(int);
int cipher(int, string);
ifstream baca;
ofstream tulis;
void encryption();
void decryption();
int choice();
void generateKeys();

bool isPrime(int x) {
	if(x <= 1) return false;
	for(int i = 2; i <= sqrt(x); i++) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}

bool areCoprime(int x, int y) {
	for(int i = 2; i <= sqrt(min(x, y)); i++) {
		if(x % i == 0 && y % i == 0) return false;
	}
	return true;
}

string trim(string s) {
	while(s.at(0) == ' ') {
		s = s.substr(1, s.length() - 1);
	}
	while(s.at(s.length() - 1) == ' ') {
		s = s.substr(0, s.length() - 1);
	}

	return s;
}

string intToBinary(int a) {
	string b = "";
	while(a != 0) {
		if(a % 2 == 1) b = "1" + b;
		else b = "0" + b;

		a /= 2;
	}
	return b;
}

int cipher(int m, string s) {
	int c = 1;
	for(int i = 0; i < s.size(); i++) {
		c = (c * c) % n;
		if(s.at(i) == '1') c = (c * m) % n;
	}
	return c;
}

void encryption() {
	cout << endl;
	string pesan;
	baca.open("plainteks.txt");
	while (!baca.eof()){
		baca >> message;
	}
	
	baca.close();
	
	cout << "Plainteks = " << pesan;
	cout << endl;
	cout << "Plaintext (angka): ";
	for(int i = 0; i < pesan.size(); i++) cout << (int)pesan.at(i) << " ";

	cout << endl;
	
	tulis.open("cipher.txt");

	for(int i = 0; i < pesan.size(); i++)
		tulis << cipher((int)pesan.at(i), intToBinary(e)) << " ";	
	tulis.close();
	cout << "Pesan yang dienkripsi sudah dimasukkan ke cipher.txt ";

	cout << "\n";
}

void decryption() {
	cout << endl;
	//cout << "Enter the components of the encrypted message separating each by a space: ";
	string input;
	char line;
	baca.open("cipher.txt");
	while (!baca.eof()){
		getline(baca, input);
		cout<<input;
	}
	
	baca.close();
	//cin.ignore();
	
	//getline(cin, input);
	input = trim(input);

	int space;
	string number;
	vector<int> numbers;
	while(input.length() != 0) {
	    	space = input.find(" ");
	    	if(space == -1) {
	    		number = input;
		    input = "";
   		}
    		else {
    			number = input.substr(0, space);
    			input = trim(input.substr(space));
    		}

	    	numbers.push_back(stoi(number));
	}

	int asciiComponents[numbers.size()];
	for(int i = 0; i < numbers.size(); i++) asciiComponents[i] = cipher(numbers.at(i), intToBinary(d));

	cout << endl;
	cout << "Dekripsi (ASCII) : ";
	for(int i = 0; i < numbers.size(); i++) cout << asciiComponents[i] << " ";

	cout << endl;
	cout << "Isi Plaintext: ";
	for(int i = 0; i < numbers.size(); i++) cout << (char)asciiComponents[i];
	
	tulis.open("plainteks.txt");

	for(int i = 0; i < numbers.size(); i++) tulis << (char)asciiComponents[i];
	
	tulis.close();
	cout << endl << "Pesan yang didekripsi sudah dimasukkan ke plainteks.txt ";

	cout << "\n";
}

int choice() {
	cout << endl;
	cout << "Public Key: (" << e << ", " << n << ")" << endl;
	cout << "Private Key: (" << d << ", " << n << ")" << endl;
	cout << "Pembangkitan Kunci (0), Enkripsi (1), Dekripsi (2), atau Keluar (acak)? ";
	string decision;
	cin >> decision;
	if(decision == "0")
		return 0;
	else if(decision == "1")
		return 1;
	else if(decision == "2")
		return 2;
	else
		return 3;
}

void generateKeys() {
	cout << endl;
	cout << "Masukkan bilangan prima (p): ";
	cin >> p;
	while(!isPrime(p)) {
		cout << p << " bukan bilangan prima, coba lagi";
		cin >> p;
	}

	cout << "Masukkan bilangan prima lagi (q): ";
	cin >> q;
	while(!isPrime(q) || q == p) {
		cout << q << " bukan bilangan prima, coba lagi";
		cin >> q;
	}

	n = p * q;
	if(n < 127) {
		cerr << "ERROR: n kurang dari 127. Program berhenti.";
		exit(1);
	}

	cout << endl;

	cout << "Nilai n = " << n << endl;
	r = (p - 1) * (q - 1);
	cout << "phi(n) = " << r << endl;
	cout << endl;
	cout << "Pilih bilangan yang relatif prima dengan phi(n): ";
	cin >> d;
	while(d <= 1 || !areCoprime(d, r)) {
		cout << d << "bukan bilangan yang relatif prima dengan phi(n), coba lagi";
		cin >> d;
	}

	cout << endl;

	int trial = 1;
	while((trial * r + 1) % d != 0) trial++;
	e = (trial * r + 1) / d;
	cout << "Pilih K untuk public key (integer positif) = " << e << " + " << r << "k: ";

	int k;
	cin >> k;
	while(k < 0) {
		cout << "Gagal, coba lagi: ";
		cin >> k;
	}
	e = e + (r * k);
}

int main() {
	cout << "TUGAS BESAR KRIPTOGRAFI" << endl;
	cout << "Algoritma RSA" << endl;
	cout << "Oleh : " <<endl;
	cout << "1. Alfin Cahyo Wibisono 14116093" << endl;
	cout << "2. Rodliyatun Nichlah Hidayati 14116068"<<endl;
	cout << "3. Ferdio Naufal Haryadi" <<endl;
	
	generateKeys();

	int choose;
	while(true) {
		choose = choice();
		if(choose == 0)
			generateKeys();
		else if(choose == 1)
			encryption();
		else if(choose == 2)
			decryption();
		else
			break;
	}

	return 0;
}
