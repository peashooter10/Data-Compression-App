#ifndef HUFFMAN_ARBORE_H
#define HUFFMAN_ARBORE_H
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 512;

class Arbore {
protected:
    int valoare;
    int nod[MAX];
    int pozitie[MAX];
    int predecesori[MAX];
    int nrNoduri;
    int copilStanga[MAX]; // 1 if this node is left child (0-bit), 0 if right (1-bit), -1 if root

public:
    Arbore(int valoare = 0);
    ~Arbore();

    static Arbore fuzionareArbori(Arbore &arbore1, Arbore &arbore2, int nodUrmator);

    void initFrunza(int simbol, int frecventa);
    int getValoare() const;

    void afisareArbore();
    void afisareCoduri(Arbore& arboreFinal, vector<int> &listaArbori);

};

#endif