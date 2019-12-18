#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


int angka[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
char huruf[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
string kata;



char conv(string kata, int i){
	int j = kata.length();
    char arrKata[j];
    strcpy(arrKata, kata.c_str());
    
	return arrKata[i];
	
}

//Hitung Bilangan Prima
int prima(int bil)
{
    int j = sqrt(bil);
    for (int i = 2; i <= j; i++)
    {
        if (bil % i == 0)
            return 0;
    }
    return 1;
}

//Cek Bilangan Prima
void CekPrima(int bil)
{
    if (prima(bil) == 0 || bil == 1)
    {
        cout << "Inputan harus bilangan prima!" << endl;
        exit(1);
    }
}


int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main()
{
	int ukuran;
	
    int p, q, n, k, on;

    cout << "Masukan kata(kapital) yang akan kamu encryption : ";
    cin >> kata;
    ukuran = kata.length();
    
    char plain[ukuran];
	int asci[ukuran];
	int chiper[ukuran];
	long int ascid[ukuran];
	char dekrip[ukuran];
    
	cout << "Pesan : "; 
    for (int i=0;i<ukuran; i++){
    	plain[i] = conv(kata, i);
		cout<< "'"<<plain[i]<<"'"<<" ";
	}
	cout<<endl;
	
	cout<<"ASCII : ";
	for (int i=0;i<ukuran; i++){
		for (int j=0;j<26;j++){
			if(plain[i] == huruf[j]){
				asci[i] = angka[j];
				cout<<"'"<<angka[j]<<"'"<<" ";
				
			}
		}
	}
	cout<<endl;
    
    cout << "p : "; cin>>p;
    CekPrima(p);
    cout << "q : "; cin>>q;
    CekPrima(q);
    n = p * q;
    cout << "n : "<<n<<endl;
    on = (p-1) * (q-1);
    cout<<"on : "<<on<<endl;
    int e = 2;
    while (e < on)
    {
        if (gcd(e, on) == 1)
        {
            break;
        }
        else
        {
            e++;
        }
    }
    cout << "e : " << e << endl;
    
    int x, d;
    for (int i = 1; i <= 10; i++)
    {
        x =  i * on + 1;
        if (x % e == 0)
        {
            d = x / e;
            break;
        }
    }
    cout << "d : " << d << endl;
    
    cout << "Enkripsi : ";
    for(int i=0 ; i<ukuran ; i++){
    	int m = pow(asci[i],e);
    	chiper[i] = m % n;
    	cout<<"'"<<chiper[i]<<"'"<<" ";
	}
	cout << endl;
	
	cout << "Dekripsi : ";
	for(int i=0 ; i<ukuran ; i++){
		long long c = pow(chiper[i],d);
		ascid[i] = c % n;
		cout<<"'"<<ascid[i]<<"'"<<" ";
	}

	return 0;
}
