#include "Lista.h"
#include <iostream>
using namespace std;

// constructor, dimensiunea Listei e nulă
Lista::Lista() {
    dimensiuneListaNoduri = 0;
}

// destructor implicit
Lista::~Lista() {}

// inițializare listă
void Lista::initializareLista(int frecvente[], int dimensiuneFrecventa) {
    for (int i = 0; i < dimensiuneFrecventa; i++) {
        if (frecvente[i] != 0) {
            Nod* n = new Nod;
            n->infoUtila.idNod = i;
            n->infoUtila.valoare = frecvente[i];
            n->infoLeg = NULL;
            n->stanga = NULL;
            n->dreapta = NULL;
            listaNoduri[dimensiuneListaNoduri++] = n;
        }
    }
}

// fuzionarea nodurilor/arborilor în lista pentru crearea arborelui Huffman
void Lista::fuzionareNoduri(int poz1, int poz2, int nodUrmator) {
    Nod* nou = new Nod;
    nou->infoUtila.idNod = nodUrmator;
    nou->infoUtila.valoare =
        listaNoduri[poz1]->infoUtila.valoare +
        listaNoduri[poz2]->infoUtila.valoare;
    nou->infoLeg = NULL;
    nou->stanga = listaNoduri[poz1];
    nou->dreapta = listaNoduri[poz2];
    listaNoduri[poz1]->infoLeg = nou;
    listaNoduri[poz2]->infoLeg = nou;

    int lo = poz1 < poz2 ? poz1 : poz2;
    int hi = poz1 < poz2 ? poz2 : poz1;

    for (int i = hi; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    for (int i = lo; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    listaNoduri[dimensiuneListaNoduri] = nou;
    dimensiuneListaNoduri++;
}

// comparator: sorteaza dupa valoare, iar la egalitate dupa idNod
// CRITIC: ambele build-uri (compresie si decompresie) trebuie sa produca
// acelasi arbore — fara tiebreaker stabil, quicksort poate ordona
// nodurile cu frecvente egale diferit si produce arbori diferiti
bool Lista::maiMic(Nod* a, Nod* b) {
    if (a->infoUtila.valoare != b->infoUtila.valoare)
        return a->infoUtila.valoare < b->infoUtila.valoare;
    return a->infoUtila.idNod < b->infoUtila.idNod;
}

// partiție pentru quicksort
int Lista::partitie(int st, int dr) {
    Nod* pivot = listaNoduri[dr];
    int i = st - 1;

    for (int j = st; j < dr; j++) {
        if (maiMic(listaNoduri[j], pivot)) {
            i++;
            swap(listaNoduri[i], listaNoduri[j]);
        }
    }

    swap(listaNoduri[i + 1], listaNoduri[dr]);
    return i + 1;
}

// quicksort
void Lista::quickSort(int st, int dr) {
    if (st < dr) {
        int p = partitie(st, dr);
        quickSort(st, p - 1);
        quickSort(p + 1, dr);
    }
}

// sortarea listei
void Lista::sortareLista() {
    if (dimensiuneListaNoduri > 1)
        quickSort(0, dimensiuneListaNoduri - 1);
}

// pentru debugging afișez lista
void Lista::afisareLista() {
    cout << "\nLista curenta:\n";
    for (int i = 0; i < dimensiuneListaNoduri; i++) {
        cout << "(" << listaNoduri[i]->infoUtila.idNod
             << ", " << listaNoduri[i]->infoUtila.valoare << ") ";
    }
    cout << '\n';
}

// generarea codurilor
void Lista::genereazaCoduri(Nod* radacina, string cod, string coduri[]) {
    if (!radacina) return;

    if (radacina->stanga == NULL && radacina->dreapta == NULL) {
        coduri[radacina->infoUtila.idNod] = cod.empty() ? "0" : cod;
        return;
    }

    genereazaCoduri(radacina->stanga, cod + "0", coduri);
    genereazaCoduri(radacina->dreapta, cod + "1", coduri);
}