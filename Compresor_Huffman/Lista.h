#ifndef LISTA_H
#define LISTA_H
#include <string>
using namespace std;

struct Info {
    int idNod;
    int valoare;
};

struct Nod {
    Info infoUtila;
    Nod* infoLeg;
    Nod* stanga;
    Nod* dreapta;
};

class Lista {
private:
    int partitie(int st, int dr);
    void quickSort(int st, int dr);
public:
    Nod listaNoduri[512]; // needs up to 2*256-1 = 511 nodes
    int dimensiuneListaNoduri;
    Lista();
    ~Lista();

    void initializareLista(int frecvente[], int dimensiuneFrecventa);
    void fuzionareNoduri(int poz1, int poz2, int nodUrmator);
    void sortareLista();
    void afisareLista();
    void genereazaCoduri(Nod* radacina, string cod, string coduri[]);
};

#endif