#include "Lista.h"
#include <iostream>
using namespace std;

Lista::Lista() {
    dimensiuneListaNoduri = 0;
}

Lista::~Lista() {}

void Lista::initializareLista(int frecvente[], int dimensiuneFrecventa) {
    for (int i = 0; i < dimensiuneFrecventa; i++) {
        if (frecvente[i] != 0) {
            listaNoduri[dimensiuneListaNoduri].infoUtila.idNod = i;
            listaNoduri[dimensiuneListaNoduri].infoUtila.valoare = frecvente[i];
            listaNoduri[dimensiuneListaNoduri].infoLeg = NULL;
            listaNoduri[dimensiuneListaNoduri].stanga = NULL;
            listaNoduri[dimensiuneListaNoduri].dreapta = NULL;
            dimensiuneListaNoduri++;
        }
    }
}

void Lista::fuzionareNoduri(int poz1, int poz2, int nodUrmator) {
    // Allocate the merged node on the heap so its address stays stable
    Nod* nou = new Nod;

    nou->infoUtila.idNod  = nodUrmator;
    nou->infoUtila.valoare =
        listaNoduri[poz1].infoUtila.valoare +
        listaNoduri[poz2].infoUtila.valoare;
    nou->infoLeg  = NULL;

    // Also heap-allocate copies of the two children so their addresses
    // don't move when we compact the array below
    Nod* child1 = new Nod(listaNoduri[poz1]);
    Nod* child2 = new Nod(listaNoduri[poz2]);

    child1->infoLeg = nou;
    child2->infoLeg = nou;

    nou->stanga = child1;
    nou->dreapta = child2;

    // Remove poz2 first (higher index), then poz1
    int lo = poz1 < poz2 ? poz1 : poz2;
    int hi = poz1 < poz2 ? poz2 : poz1;

    for (int i = hi; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    for (int i = lo; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    // Place the merged node at the end of the active list
    listaNoduri[dimensiuneListaNoduri] = *nou;
    dimensiuneListaNoduri++;
}

int Lista::partitie(int st, int dr) {
    int pivot = listaNoduri[dr].infoUtila.valoare;
    int i = st - 1;

    for (int j = st; j < dr; j++) {
        if (listaNoduri[j].infoUtila.valoare < pivot) {
            i++;
            swap(listaNoduri[i], listaNoduri[j]);
        }
    }

    swap(listaNoduri[i + 1], listaNoduri[dr]);
    return i + 1;
}

void Lista::quickSort(int st, int dr) {
    if (st < dr) {
        int p = partitie(st, dr);
        quickSort(st, p - 1);
        quickSort(p + 1, dr);
    }
}

void Lista::sortareLista() {
    if (dimensiuneListaNoduri > 1)
        quickSort(0, dimensiuneListaNoduri - 1);
}

void Lista::afisareLista() {
    cout << "\nLista curenta:\n";
    for (int i = 0; i < dimensiuneListaNoduri; i++) {
        cout << "(" << listaNoduri[i].infoUtila.idNod
             << ", " << listaNoduri[i].infoUtila.valoare << ") ";
    }
    cout << '\n';
}

void Lista::genereazaCoduri(Nod* radacina, string cod, string coduri[]) {
    if (!radacina) return;

    if (radacina->stanga == NULL && radacina->dreapta == NULL) {
        // Edge-case: single-symbol file gets code "0"
        coduri[radacina->infoUtila.idNod] = cod.empty() ? "0" : cod;
        return;
    }

    genereazaCoduri(radacina->stanga, cod + "0", coduri);
    genereazaCoduri(radacina->dreapta, cod + "1", coduri);
}