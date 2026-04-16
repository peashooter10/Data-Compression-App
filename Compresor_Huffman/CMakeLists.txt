cmake_minimum_required(VERSION 3.7)
project(Compresor_Huffman)

# versiunea limbajului c++
set(CMAKE_CXX_STANDARD 20)

# fie un fișier main.cpp în care se apelează o bibliotecă pentru o parte din program
# de exemplu, cstring pentru utilizarea stringurilor în c++
# la rulare, programul se uită în memoria calculatorului la acea bibliotecă pentru a-și lua ce are nevoie
# acesta este un caz de LINK DINAMIC
# în schimb, dacă vrem ca programul să aibă scris în el biblioteca pe care o folosește
# folosim un LINK STATIC
# în cazul unei aplicații care apelează fișiere executabile, trebuie să fie folosite LINK-URI STATICE
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# adaug fișierele .cpp la executabil
add_executable(Compresor_Huffman
        main.cpp
        Lista.cpp
)