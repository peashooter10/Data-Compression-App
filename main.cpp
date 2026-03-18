#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Arbore.h"
using namespace std;
const int DIM=4096;

int main() {
    //declaratii
    int i;//contor pentru for
    int dimensiuneFisier,sumaFrecvente=0;
    int frecventa[DIM]={0};//frecventa cu care apar diferitele caractere/simboluri in text/fisier
    string fisier;

    fisier = "jumper.mp3";//dau numele fisierului pe care vreau sa il citesc binar

    ifstream file(fisier, ios::binary);//citesc fisierul in mod binar, bit cu bit

    //daca fisierul nu exista inchid programul
    if (!file.is_open()) {
        cerr << "eroare, nu exista fisierul\n";
        return 1;
    }

    //declar si definesc un vector dinamic de tip unsigned char
    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>()));
    file.close();

    dimensiuneFisier=buffer.size();

    //contorizez
    for (i=0; i<buffer.size(); ++i) {
        frecventa[buffer[i]]++;
    }

    //
    for (i = 0; i < 4096; ++i) {
        if (frecventa[i] > 0) {
            cout << "0x" << hex << setw(2) << setfill('0') << i
                 << " : " << dec << frecventa[i] << "\n";
        sumaFrecvente=sumaFrecvente+frecventa[i];
        }
    }

    if (sumaFrecvente==buffer.size())
        cout<<"e bine, sunt "<< sumaFrecvente << " de bytes";

    return 0;
}