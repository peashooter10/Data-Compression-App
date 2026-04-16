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
            Nod* n = new Nod; // creez un nou nod
            n->infoUtila.idNod = i; // atribui un id nou nodului
            n->infoUtila.valoare = frecvente[i]; // atribui frectvența respectivă
            // pointerii sunt nuli pentru că încă nu indică spre nimic
            n->infoLeg = NULL;
            n->stanga = NULL;
            n->dreapta = NULL;
            listaNoduri[dimensiuneListaNoduri++] = n; // cresc dimensiunea listei
        }
    }
}

// fuzionarea nodurilor/arborilor în lista pentru crearea arborelui Huffman
void Lista::fuzionareNoduri(int poz1, int poz2, int nodUrmator) {
    Nod* nou = new Nod; // creez un nod nou care va fi tatăl celor doi arbori
    nou->infoUtila.idNod = nodUrmator; // id-ul noului nou ia valoarea urm nod
    nou->infoUtila.valoare =
        listaNoduri[poz1]->infoUtila.valoare +
        listaNoduri[poz2]->infoUtila.valoare;
    nou->infoLeg = NULL; // nodul nou nu are predecesor(nod tată)
    // nodul nou are acuma doi fii
    nou->stanga = listaNoduri[poz1];
    nou->dreapta = listaNoduri[poz2];
    // cei doi fii au un tată
    listaNoduri[poz1]->infoLeg = nou;
    listaNoduri[poz2]->infoLeg = nou;

    // în lo(low) și hi(high) salvez care este cea mai mare valoare dintre poz1 și poz2
    int lo = poz1 < poz2 ? poz1 : poz2;
    int hi = poz1 < poz2 ? poz2 : poz1;

    // elimin cele două noduri pe care le fuzionez din listaNoduri
    for (int i = hi; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    for (int i = lo; i < dimensiuneListaNoduri - 1; i++)
        listaNoduri[i] = listaNoduri[i + 1];
    dimensiuneListaNoduri--;

    listaNoduri[dimensiuneListaNoduri] = nou; // nou este inserat în listaNoduri pe ultima poziție
    dimensiuneListaNoduri++; // cresc dimensiunea listei
    // astfel, la fiecare fuzionare dimensiunea listei scade cu 1
}

// comparator: sortează dupa valoarea nodului, iar la egalitate dupa idNod
bool Lista::maiMic(Nod* a, Nod* b) {
    if (a->infoUtila.valoare != b->infoUtila.valoare)
        return a->infoUtila.valoare < b->infoUtila.valoare;
    return a->infoUtila.idNod < b->infoUtila.idNod;
}

// partiție pentru quicksort
int Lista::partitie(int st, int dr) {
    Nod* pivot = listaNoduri[dr]; // aleg un pivot
    int i = st - 1;

    for (int j = st; j < dr; j++) { // parcurg elementele de la st la dr
        if (maiMic(listaNoduri[j], pivot)) { // dacă elementul este mai mic decît pivotul îl mut după pivot
            i++;swap(listaNoduri[i], listaNoduri[j]);
        }
    }

    swap(listaNoduri[i + 1], listaNoduri[dr]);
    return i + 1; //returnez poziția noului pivot
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
    if (!radacina) return; // dacă nu am rădăcina arborelui încă nu pot genera codurile

    // dacă am ajuns la un nod frunză returnez cod.empty()
    // în cazul în care fișierul are un singur caracter îi atribui codul 0
    if (radacina->stanga == NULL && radacina->dreapta == NULL) {
        coduri[radacina->infoUtila.idNod] = cod.empty() ? "0" : cod;
        return;
    }

    genereazaCoduri(radacina->stanga, cod + "0", coduri); // merg la stânga adaug 0 la finalul codului
    genereazaCoduri(radacina->dreapta, cod + "1", coduri); // merg la dreapta adaug 1 la finalul codului
}