#include "Arbore.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// constructor — asignezi fiecare parametru cu this->
Arbore::Arbore(int valoare) {
    this->valoare = valoare;
    nrNoduri = 0;

    for (int i = 0; i < MAX; i++) {
        nod[i] = 0;
        pozitie[i] = 0;
        predecesori[i] = -1;
        copilStanga[i] = -1;
    }
}

Arbore::~Arbore() {}

Arbore Arbore::fuzionareArbori(Arbore &arbore1, Arbore &arbore2, int nodUrmator) {
    Arbore arboreFinal(arbore1.valoare + arbore2.valoare);

    int i;

    // --- copiere arbore1 ---
    for (i = 0; i < arbore1.nrNoduri; i++) {
        arboreFinal.nod[i]         = arbore1.nod[i];
        arboreFinal.pozitie[i]     = arbore1.pozitie[i];
        arboreFinal.predecesori[i] = arbore1.predecesori[i];
        arboreFinal.copilStanga[i] = arbore1.copilStanga[i];
    }

    int offset = arbore1.nrNoduri;

    // --- copiere arbore2 ---
    for (int j = 0; j < arbore2.nrNoduri; j++) {
        arboreFinal.nod[offset + j]     = arbore2.nod[j];
        arboreFinal.pozitie[offset + j] = arbore2.pozitie[j];
        arboreFinal.copilStanga[offset + j] = arbore2.copilStanga[j];

        if (arbore2.predecesori[j] == -1)
            arboreFinal.predecesori[offset + j] = -1;
        else
            arboreFinal.predecesori[offset + j] = arbore2.predecesori[j] + offset;
    }

    // --- noul nod radacina ---
    int root  = offset + arbore2.nrNoduri;
    int root1 = arbore1.nrNoduri - 1;           // radacina arbore1
    int root2 = offset + arbore2.nrNoduri - 1;  // radacina arbore2

    arboreFinal.nod[root]         = nodUrmator;
    arboreFinal.predecesori[root] = -1;
    arboreFinal.copilStanga[root] = -1;

    // --- linkam explicit cele 2 radacini vechi ---
    arboreFinal.predecesori[root1] = root;
    arboreFinal.copilStanga[root1] = 1;  // stanga → bit 0

    arboreFinal.predecesori[root2] = root;
    arboreFinal.copilStanga[root2] = 0;  // dreapta → bit 1

    arboreFinal.nrNoduri = root + 1;

    return arboreFinal;
}

void Arbore::initFrunza(int simbol, int frecventa) {
    valoare = frecventa;
    nrNoduri = 1;

    nod[0] = simbol;
    predecesori[0] = -1;
}

int Arbore::getValoare() const {
    return valoare;
}

void Arbore::afisareArbore() {
    cout << "X={";
    for (int i = 0; i < nrNoduri; i++) {
        cout << nod[i];
        if (i != nrNoduri - 1) cout << ",";
    }
    cout << "}\n";

    cout << "U={";
    bool prima = true;

    for (int i = 0; i < nrNoduri; i++) {
        if (predecesori[i] != -1) {
            if (!prima) cout << ",";
            cout << "[" << nod[predecesori[i]] << "," << nod[i] << "]";
            prima = false;
        }
    }

    cout << "}\n";
}

void Arbore::afisareCoduri(Arbore &arboreFinal, vector<int> &arbori) {
    cout << "\n=== Coduri Huffman ===\n";

    for (int i = 0; i < arboreFinal.nrNoduri; i++) {
        // check if leaf — no node has this as parent
        bool frunza = true;
        for (int j = 0; j < arboreFinal.nrNoduri; j++) {
            if (arboreFinal.predecesori[j] == i) {
                frunza = false;
                break;
            }
        }
        if (!frunza) continue;

        string cod = "";
        int curent = i;

        // climb to root
        while (arboreFinal.predecesori[curent] != -1) {
            // copilStanga[curent] == 1 → left child → bit '0'
            // copilStanga[curent] == 0 → right child → bit '1'
            cod += (arboreFinal.copilStanga[curent] == 1) ? '0' : '1';
            curent = arboreFinal.predecesori[curent];
        }

        reverse(cod.begin(), cod.end());

        cout << "Nod " << arboreFinal.nod[i] << " -> " << cod << "\n";
    }
}