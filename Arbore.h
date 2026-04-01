#ifndef HUFFMAN_ARBORE_H
#define HUFFMAN_ARBORE_H
#include <iostream>
#include <vector>
using namespace std;

class Arbore {
protected:
    int valoare;
    vector<int> nod;
    vector<int> pozitie;
    vector<int> predecesori;
public:
    Arbore(int valoare, vector<int> nod, vector<int> pozitie, vector<int> predecesori);
    ~Arbore();

    Arbore fuzionareArbori(Arbore &arbore1, Arbore &arbore2, int nodUrmator);//fuzionare 2 arbori

    void afisareArbore(Arbore &arbore);

};

#endif //HUFFMAN_ARBORE_H
