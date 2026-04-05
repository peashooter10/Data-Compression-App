#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Arbore.h"

using namespace std;

const int DIMENSIUNE = 256;

int main() {
    int i,sumaFrecvente=0,dimensiuneFisier=0;
    string fisier = "exemplu.txt";
    ifstream file(fisier, ios::binary);

    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului!\n";
        return 1;
    }

    // --- citire fisier ---
    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>())
    );
    file.close();

    // --- calcul frecvente ---
    int frecventa[DIMENSIUNE] = {0};

    for (unsigned char c : buffer) {
        frecventa[c]++;
    }

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
        cout<<"e bine, sunt "<< sumaFrecvente << " de bytes\n";


    // --- creare arbori initiali ---
    vector<Arbore> arbori;

    for (int i = 0; i < DIMENSIUNE; i++) {
        if (frecventa[i] > 0) {
            Arbore a;
            a.initFrunza(i, frecventa[i]);
            arbori.push_back(a);
        }
    }

    // --- construire arbore Huffman ---
    int nodUrmator = 256;

    while (arbori.size() > 1) {
        sort(arbori.begin(), arbori.end(),
            [](const Arbore &a, const Arbore &b) {
                return a.getValoare() < b.getValoare();
            });

        Arbore nou = Arbore::fuzionareArbori(
            arbori[0], arbori[1], nodUrmator++
        );

        arbori.erase(arbori.begin());
        arbori.erase(arbori.begin());

        arbori.push_back(nou);
    }

    if (arbori.empty()) {
        cout << "Fisier gol.\n";
        return 0;
    }

    Arbore arboreFinal;
    arboreFinal=arbori[0];

    // ===============================
    // 🌳 AFISARE ARBORE
    // ===============================
    cout << "\n=== Arbore (X si U) ===\n";
    arboreFinal.afisareArbore();

    return 0;
}