#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
#include "Lista.h"

using namespace std;

const int DIMENSIUNE = 256;

string extensieFaraSlash(const string& fisier) {
    // extrag numele fișierului, fără directoare
    size_t slash = fisier.find_last_of("/\\"); // găsesc ultimul "\\" din path-ul fișierului
    string numeFisier = (slash == string::npos) ? fisier : fisier.substr(slash + 1); // elimin tot ce e înainte
    return numeFisier + ".huff"; // returnez numele fișierului + extensia .huff
}

// compresia fișierului
void comprima(const string& fisier, const string& outputFolder) {
    ifstream file(fisier, ios::binary); // citesc fișierul ca succesiune de biți
    if (!file.is_open()) { cerr << "Eroare la deschiderea fisierului!\n"; return; }

    // în buffer salvez fișierul
    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>())
    );
    file.close();

    if (buffer.empty()) { cerr << "Fișierul este gol!\n"; return; }

    cout << "Fișier citit: " << buffer.size() << " bytes\n";

    // frecvențe
    int frecventa[DIMENSIUNE] = {0}; // în frecventă salvez frecvența fiecărui grup de biți/byte
    for (unsigned char c : buffer) frecventa[c]++; // pentru fiecare caracter din buffer cresc frecvența

    // arbore Huffman
    Lista lista; // creez o listă de noduri
    lista.initializareLista(frecventa, DIMENSIUNE); // inițializez lista
    int nodUrmator = 256; // nodUrmator este id-ul urm nod care va fi creat

    /*
     * Algoritmul Huffman explicat in a nutshell:
     * Fie Lista o listă care conține noduri, fiecare cu un id și o valoare
     * La inițializarea listei Lista are 256 de elemente, maximul de combinații de biți, iar elementele au valoarea egală cu frecvența respectivă
     * Lista este sortată descrescător în funcție de valoarea nodului
     * Se iau ultimele 2 noduri și se fuzionează, astfel este creat un nou nod tată
     * Astfel cele două noduri legate de nodul tată devin un arbore, iar valoarea nodului tată va fi cea luată în considerare la ordonarea listei
     * Procesul se repetă până se obține un arbore binar
     * Parcurgând arborele binar se poate lua la stânga sau la dreapta
     * În funcție de direcția aleasă se atribuie un cod prin care valoarea va fi reprezentată în fișierul comprimat
     */

    while (lista.dimensiuneListaNoduri > 1) { // cât timp avem un arbore în listă
        lista.sortareLista(); // sortez lista
        lista.fuzionareNoduri(0, 1, nodUrmator++); // fuzionez nodurile
    }

    Nod* radacina = lista.listaNoduri[0]; // salvez nodul rădăcină

    // generez codurile
    string coduri[256];
    lista.genereazaCoduri(radacina, "", coduri);

    // codificare biți
    vector<unsigned char> output; // vector de caractere
    unsigned char byte = 0;
    int bitCount = 0; // numărul de biți

    for (unsigned char c : buffer) { // pentu fiecare byte din buffer
        for (char bit : coduri[c]) { // pentru fiecare bit din lista de coduri
            byte <<= 1;
            if (bit == '1') byte |= 1;
            if (++bitCount == 8) {
                output.push_back(byte);
                byte = 0; bitCount = 0;
            }
        }
    }

    int bitiRamasi = bitCount;
    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        output.push_back(byte);
    }

    /*
    Scrierea fișierului comprimat
    Header compact:
      [1 byte]  numar caractere unice
      [5 bytes] per caracter unic: 1 byte id + 4 bytes frecventa
      [4 bytes] dimensiunea originala (pentru decompresie exacta)
      [1 byte]  biti ramasi in ultimul byte
      [n bytes] date comprimate
    */

    string numeFisier = outputFolder + extensieFaraSlash(fisier); // salvez numele fișierului
    ofstream out(numeFisier, ios::binary);
    if (!out.is_open()) { cerr << "Nu pot crea fisierul de iesire!\n"; return; }

    // număr caractere unice din fișier
    // folosesc unsigned short (2 bytes) pentru că pot exista maxim 256 valori diferite
    unsigned short unice = 0;
    for (int i = 0; i < 256; i++) if (frecventa[i]) unice++;
    out.write((char*)&unice, sizeof(unice));

    // pentru fiecare caracter unic scriu:
    // [1 byte] caracterul
    // [4 bytes] frecvența lui
    // pentru reconstruirea arborelui
    for (int i = 0; i < 256; i++) {
        if (frecventa[i]) {
            unsigned char c = (unsigned char)i;
            out.write((char*)&c, 1);
            out.write((char*)&frecventa[i], sizeof(int));
        }
    }

    // dimensiunea originală a fișierului (în bytes)
    // ca să știu exact când să mă opresc la decompresie
    unsigned int dimOriginala = (unsigned int)buffer.size();
    out.write((char*)&dimOriginala, sizeof(dimOriginala));

    // numărul de biți valizi din ultimul byte
    // deoarece ultimul byte poate fi incomplet (padding)
    unsigned char br = (unsigned char)bitiRamasi;
    out.write((char*)&br, 1);

    // scriu efectiv datele comprimate (vectorul de bytes rezultat)
    // output.data() e pointer la primul element din vector
    // output.size() e numărul total de bytes
    if (!output.empty())
        out.write((char*)output.data(), output.size());

    out.close();

    // date pentru debugging
    long long headerSize = 2 + (int)unice * 5 + 4 + 1;
    long long totalComprimat = headerSize + (long long)output.size();
    double ratio = 100.0 * (1.0 - (double)totalComprimat / buffer.size());

    cout << "SUCCESS\n";
    cout << "original_bytes=" << buffer.size() << "\n";
    cout << "comprimat_bytes=" << totalComprimat << "\n";
    cout << "reducere=" << ratio << "\n";
    cout << "output=" << numeFisier << "\n";
}

// main acceptă 3 argumente, executabilul, path-ul fișierului original și folderul de ieșire
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "EROARE: Usage: CompresorHuffman <fisier_intrare> <folder_iesire>\n";
        return 1;
    }
    comprima(argv[1], argv[2]);

    return 0;
}