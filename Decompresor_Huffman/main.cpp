#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Lista.h"
using namespace std;

const int DIMENSIUNE = 256;

string extensieFaraSlash(const string& fisier) {
    // extrag numele fișierului, fără directoare
    size_t slash = fisier.find_last_of("/\\"); // găsesc ultimul "\\" din path-ul fișierului
    string numeFisier = (slash == string::npos) ? fisier : fisier.substr(slash + 1); // elimin tot ce e înainte
    return numeFisier + ".huff"; // returnez numele fișierului + extensia .huff
}

void decomprima(const string& fisierHuff, const string& outputFolder, const string& numeFisierOut) {
    cout << "Deschid: " << fisierHuff << "\n" << flush; // deschid fișierul
    ifstream file(fisierHuff, ios::binary); // citesc fișierul în mod binar
    if (!file.is_open()) {
        cout << "EROARE: Nu pot deschide: " << fisierHuff << "\n" << flush;
        return;
    }
    cout << "Fisier deschis cu succes!\n" << flush;

    // citesc header-ul
    unsigned short unice;
    file.read((char*)&unice, sizeof(unice));

    // citind header-ul atribui frecvențele caracterelor
    int frecventa[DIMENSIUNE] = {0};
    for (int i = 0; i < unice; i++) {
        unsigned char c; int fr;
        file.read((char*)&c, 1); // citesc caracterul (1 byte)
        file.read((char*)&fr, sizeof(int)); // citesc frecvența lui (4 bytes)
        frecventa[(int)c] = fr; // refac frecvența
    }

    // citesc dimensiunea originală a fișierului, mă opresc la capăt
    unsigned int dimOriginala;
    file.read((char*)&dimOriginala, sizeof(dimOriginala));

    // citesc câți biți sunt valizi în ultimul byte
    // ultimul byte poate avea padding
    unsigned char br;
    file.read((char*)&br, 1);
    int bitiRamasi = (int)br;

    // citesc restul datelor comprimate
    vector<unsigned char> comprimat( // în comprimat am conținutul fișierului salvat ca un vector de caractere
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>())
    );
    file.close();

    // reconstruiesc arborele
    // creez o listă și o inițializez
    Lista lista;
    lista.initializareLista(frecventa, DIMENSIUNE);
    int nodUrmator = 256;
    while (lista.dimensiuneListaNoduri > 1) {
        lista.sortareLista();
        lista.fuzionareNoduri(0, 1, nodUrmator++);
    }
    Nod* radacina = lista.listaNoduri[0];

    // decodificare
    vector<unsigned char> output; // aici reconstruiesc fișierul original
    Nod* curent = radacina; // pointer pentru parcurgerea arborelui
    unsigned int scrise = 0; // câți bytes am reconstruit

    // parcurg fiecare byte din datele comprimate
    for (int i = 0; i < (int)comprimat.size() && scrise < dimOriginala; i++) {
        unsigned char byte = comprimat[i];
        int bitsInByte = (i == (int)comprimat.size() - 1)
                         ? (bitiRamasi > 0 ? bitiRamasi : 8) : 8;

        // parcurg fiecare bit
        for (int b = 7; b >= 8 - bitsInByte && scrise < dimOriginala; b--) {
            int bit = (byte >> b) & 1;
            curent = bit ? curent->dreapta : curent->stanga;

            // merg în arbore
            if (!curent->stanga && !curent->dreapta) {
                output.push_back((unsigned char)curent->infoUtila.idNod);
                scrise++;
                curent = radacina;
            }
        }
    }

    // scrie fisier decompresat
    string caleFisierOut = outputFolder + numeFisierOut;
    // deschid fișierul în mod binar
    ofstream out(caleFisierOut, ios::binary);
    if (!out.is_open()) { cerr << "Nu pot crea fisierul decompresat!\n"; return; }
    // scriu tot conținutul reconstruit
    // output.data() e pointer la date
    // output.size() e numărul de bytes
    out.write((char*)output.data(), output.size());
    out.close();

    cout << "SUCCESS\n";
    cout << "decompresat_bytes=" << output.size() << "\n";
    cout << "output=" << caleFisierOut << "\n";
}

// main acceptă 4 argumente, executabilul, fișierul comprimat, folderul de ieșire și numele folderului de ieșire
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "EROARE: Usage: DecompresorHuffman <fisier.huff> <folder_iesire> <nume_fisier_iesire>\n";
        return 1;
    }
    decomprima(argv[1], argv[2], argv[3]);
    return 0;
}