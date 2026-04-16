#ifndef LISTA_H
#define LISTA_H
#include <string>
using namespace std;


// structura info pentru informațiile utile, id-ul nodului și valoarea sa
struct Info {
    int idNod;
    int valoare;
};

// nodul are informația utilă și alți pointeri de tip nod
struct Nod {
    Info infoUtila;
    Nod* infoLeg; // pointer către nodul „tată”
    Nod* stanga; // pointer către nodul „fiu” din stânga
    Nod* dreapta; // pointer către nodul „fiu” din dreapta
};

// clasa Lista este formată din lista de noduri ce fac parte din arborele Huffman
class Lista {
private:
    // funcțiile pentru sortarea listei
    bool maiMic(Nod* a, Nod* b);
    int partitie(int st, int dr);
    void quickSort(int st, int dr);
public:
    Nod* listaNoduri[512]; // lista de pointeri de tip nod are maxim 511 de noduri
    int dimensiuneListaNoduri; // dimensiunea listei de noduri
    Lista(); // constructor
    ~Lista(); // destructor

    void initializareLista(int frecvente[], int dimensiuneFrecventa);
    void fuzionareNoduri(int poz1, int poz2, int nodUrmator); // fuzionarea nodurilor
    void sortareLista();
    void afisareLista();
    void genereazaCoduri(Nod* radacina, string cod, string coduri[]); // atribui codurile
};

#endif