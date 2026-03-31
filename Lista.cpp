#include "Lista.h"
#include <iostream>
using namespace std;
//incerc ceva

Nod (Nod &nod) {
    //supradefinesc operatorul + pentru a fuziona 2 arbori
    //nod1=nod1+nod2
    int i,j;
    for (i=0;i<size(nod.infoUtile.indice);i++) {
        for (j=0;j<size(nod.infoUtile.indice);j++) {
            nod.infoUtile.indice[i] = 0;
        }
    }

}

Arbore operator<(Arbore &arbore1, Arbore &arbore2) {

}

//constructor
Lista::Lista() {
    //initializez primul si ultimul cu nod cu null
    //pentru ca lista e goala si cei doi pointeri coincid
    prim = NULL;
    ultim = NULL;
}

//destructor
Lista::~Lista() {
    //parcurg toate elementele din lista
    Nod* curent = prim;
    while (curent) {
        Nod* urmator = curent->infoLeg;//pun infoLeg in urmatorul ca sa pot sterge
        delete curent;//sterg elementul curent
        curent = urmator;//trec la urmatorul element
    }
}

void Lista::adaugareNodSfarsit(Arbore sfarsit) {
    Nod* nou = new Nod;
    nou->infoUtile = sfarsit;//copiez informatiile
    nou->infoLeg = NULL;//setez infoLeg cu null ca am ajuns in interiorul listei
    if (prim) {//daca lista nu e goala
        ultim->infoLeg = nou;//pun infoLeg din nodul nou ultimul nod
    } else {
        prim = nou;
    }
    ultim = nou;
}

void Lista::afisareLista() {
    //afisez elementele parcurgand lista cu un for
    for (Nod* a = prim; a; a = a->infoLeg) {
        cout << a->infoUtile.nr << ' ' << a->infoUtile.nume << '\n';
    }
}
