#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "Lista.h"

using namespace std;

const int DIMENSIUNE = 256;

string createNumeFisierComprimat(string fisier) {
    return fisier + ".huff";
}

int main() {
    string fisier = "wordpad.exe";
    string numeFisierComprimat;
    numeFisierComprimat= createNumeFisierComprimat(fisier);

    ifstream file(fisier, ios::binary);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului!\n";
        return 1;
    }

    // --- citire fisier ---
    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>())
    );
    file.close();

    cout << "Fisier citit: " << buffer.size() << " bytes\n";

    // --- calcul frecvente ---
    int frecventa[DIMENSIUNE] = {0};

    for (unsigned char c : buffer) {
        frecventa[c]++;
    }

    // --- initializare lista ---
    Lista lista;
    lista.initializareLista(frecventa, DIMENSIUNE);

    int nodUrmator = 256;

    // --- construire arbore Huffman ---
    while (lista.dimensiuneListaNoduri > 1) {
        lista.sortareLista();
        lista.fuzionareNoduri(0, 1, nodUrmator++);
    }
    cout << "Am ajuns dupa arbore\n";

    Nod* radacina = &lista.listaNoduri[0];

    // --- generare coduri ---
    string coduri[256];
    lista.genereazaCoduri(radacina, "", coduri);

    // --- debug coduri ---
    cout << "\nCoduri Huffman:\n";
    for (int i = 0; i < 256; i++) {
        if (!coduri[i].empty()) {
            cout << char(i)<< "(" << i << ")" " -> " << coduri[i] << "\n";
        }
    }

    // --- compresie pe biti ---
    vector<unsigned char> output;
    unsigned char byte = 0;
    int bitCount = 0;

    for (unsigned char c : buffer) {
        string cod = coduri[c];

        for (char bit : cod) {
            byte <<= 1;

            if (bit == '1')
                byte |= 1;

            bitCount++;

            if (bitCount == 8) {
                output.push_back(byte);
                byte = 0;
                bitCount = 0;
            }
        }
    }

    int bitiRamasi = bitCount;

    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        output.push_back(byte);
    }

    cout << "Dimensiune output: " << output.size() << " bytes\n";

    // --- path sigur ---
    string path = filesystem::current_path().string() + "/" + numeFisierComprimat;
    cout << "Se salveaza in: " << path << endl;

    // --- scriere fisier ---
    ofstream out(path, ios::binary);

    if (!out.is_open()) {
        cerr << "EROARE: Nu pot crea fisierul!\n";
        return 1;
    }

    // frecvente
    out.write((char*)frecventa, sizeof(frecventa));

    // biti ramasi
    out.write((char*)&bitiRamasi, sizeof(bitiRamasi));

    // date comprimate
    if (!output.empty()) {
        out.write((char*)output.data(), output.size());
    }

    out.close();

    cout << "\nCompresie finalizata!\n";

    return 0;
}