#ifndef HUFFMAN_LISTA_H
#define HUFFMAN_LISTA_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Arbore {
private:
    int valoare,indiceArbore;
    vector<unsigned int> indice;
    vector<unsigned int> noduri;
    vector<unsigned int> predecesori;
public:
    void citireArbore(string fisier);
    void afisareArbore(Arbore arbore);
};

struct Nod {
    Arbore infoUtile;
    Nod* infoLeg;
    Nod operator+(Nod &nod);
    Nod operator<(Nod &nod);
};

class Lista {
protected://declar primul si ultimul nod din lista
    Nod* prim;
    Nod* ultim;
public:
    Lista();//constructor
    ~Lista();//destructor

    void adaugareNodSfarsit(Arbore sfarsit);//functie sa adaug un nod la final

    void afisareLista();

};



#endif
