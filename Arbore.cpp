#include "Arbore.h"
#include <iostream>
#include <vector>
using namespace std;

Arbore::Arbore(int valoare, vector<int> nod, vector<int> pozitie, vector<int> predecesori){
    valoare = 0;
}

Arbore Arbore::fuzionareArbori(Arbore &arbore1, Arbore &arbore2, int nodUrmator) {
    int valoareFinala;
    vector<int> nodFinala;
    vector<int> pozitieFinala;
    vector<int> predecesoriFinala;
    int i,j,k;

    valoareFinala = arbore1.valoare+arbore2.valoare;

}
