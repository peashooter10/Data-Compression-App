# Roadmap
## Scop și funcționalitate
Aplicația are rolul principal de a comprima fișiere într-un format _fără pierderi_ (lossless), fișierul rezultat fiind mai mic ca dimensiune, însă calitatea rămâne aceeași după procesul de decompresie. Este o aplicație Desktop pentru Windows care implementează algoritmul Huffman.

Pentru a exemplifica compresia _fără pierderi_, șirul „AAABCDDD” poate fi comprimat, transformându-se în „3ABC3D”. Astfel, fișierul comprimat poate fi reconvertit în fișierul original.

În schimb, o melodie comprimată poate pierde unele note muzicale unice și mai greu de observat ale interpretului sau ale instrumentului. Totuși, revenirea fișierului la starea sa originală este imposibilă, deoarece acele caracteristici sunt pierdute definitiv.

## Dezvoltare
Aplicația de comprimare a datelor folosind algoritmul Huffman a fost dezvoltat în C++ 20 folosind _CLion_, generând 2 fișiere .exe: compresorul și decompresorul. Aceste fișiere .exe fac parte dintr-o aplicație Java creată în _Apache NetBeans_. Fișierul .jar generat a fost transformat într-un .exe pentru utilizatorii Windows cu ajutorul aplicației _Launch4j_. Folosind _GitHub Desktop_, proiectul a fost finalizat și încărcat pe _GitHub_, iar cu ajutorul _GitHub Actions_, proiectul este compilat pentru a rula pe Windows/Linux/Mac.

## Piața
Pe piața actuală există o gamă largă de aplicații specializate în comprimarea datelor, cele mai cunoscute fiind WinRAR sau 7-Zip, ambele având interfețe și funcționalități similare.

## Planificare
Săptămâna 1: Roadmap, analiza problemei, alegerea mediului de dezvoltare, implementarea în consolă a algoritmului Huffman, atât pentru compresie, cât și pentru decompresie\
Săptămâna 2: Crearea aplicației de bază cu interfață grafică prietenoasă și butoane, implementarea unui cod simplu pentru testarea funcționalității aplicației\
Săptămâna 3: Dezvoltarea scriptului pentru selectarea unui fișier și afișarea unui preview în consolă pentru verificare\
Săptămâna 4: Integrarea aplicației din Apache NetBeans cu algoritmii Huffman de compresie și decompresie scriși în C++\
Săptămâna 5: Testarea aplicației pe o gamă variată de fișiere\
Săptămâna 6: Dezvoltarea aplicației pentru Windows/Linux/Mac\
Săptămâna 7: Testare\
Săptămâna 8: Alte idei\

## Link-uri:  
CLion: https: //www.jetbrains.com/clion/download/?section=windows\
Apache NetBeans: https://netbeans.apache.org/front/main/download/\  
Launch4j: https://sourceforge.net/projects/launch4j/\  
GitHub Desktop: https://desktop.github.com/download/\  
GitHub Actions: https://github.com/features/actions\  

