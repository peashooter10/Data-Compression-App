#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const int DIMENSIUNE = 256;



int main() {
    string fisier = "exemplu.txt";
    ifstream file(fisier, ios::binary);

    if (!file.is_open()) {
        cerr << "eroare, nu exista fisierul\n";
        return 1;
    }

    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>()));
    file.close();

    int frecventa[DIMENSIUNE] = {0};
    for (size_t i = 0; i < buffer.size(); ++i) {
        frecventa[buffer[i]]++;
    }



    int sumaFrecvente = 0;
    for (int i = 0; i < DIMENSIUNE; ++i) {
        if (frecventa[i] > 0) {
            cout << "0x" << hex << setw(2) << setfill('0') << i
                 << " : " << dec << frecventa[i] << "\n";
            sumaFrecvente += frecventa[i];
        }
    }

    if (sumaFrecvente == (int)buffer.size())
        cout << "\ne bine, sunt " << sumaFrecvente << " bytes\n";

    return 0;
}