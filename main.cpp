// Krzysztof_Gorski_245079
// Projekt 2 
// Grafy

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <list>                  //list - wykorzystywane jedsynie w trakcie generowania grafu 
#include <time.h>      // nie wplywa w zaden sposob na implementacje algorytmow ani struktur
#include <chrono>
#include "Graf.cpp"

using namespace std;

#define DT int  // definicja rodzaju danych np. int, duble, float
#define RANGE  10  // zakres wartowsci wag 
#define LOOPS 100 

template<typename T>
void wybor1(Graf<T>* GRAF){
    GRAF->read_from_file();
    int wybor, nowy;
    bool b=true;
    while (true) {
     
        cout << "Wybierz opcje: " << endl
            << "1 \t" << "wyswietl tablice sasiedztwa\t \n"
            << "2 \t" << "wyswietl macierz\t \n"
            << "3 \t" << "znajdz droge dla obecnego grafu (na liscie)\t \n"
            << "4 \t" << "znajdz droge dla obecnego grafu (na macierzy)\t \n"
            << "5 \t" << "pokaz droge oraz koszta\t \n"
            << "6 \t" << "zmien wierzcholek startowy\t \n"
            << "0 \t" << "- zakoncz - \t \n";
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            GRAF->print_List();
            cin.get();
            break;
        case 2:
            GRAF->print_Matrix();
            cin.get();
            break;
        case 3:
            GRAF->BF_for_list();
            cout << "znaleziono" << endl;
            break;
        case 4:
            GRAF->BF_for_matrix();
            cout << "znaleziono" << endl;
            break;
        case 5:
            GRAF->print_Cost();
            GRAF->write_Patch();
            cout << "\n sciezke zapisano do pliku \n";
            cin.get();
            break;
        case 6:
            cout << "zakres od 0 do " << GRAF->return_V_num() << endl;
            cin >> nowy;
            GRAF->set_Start(nowy);
            break;
        case 0:
            b = false;
            break;
        default:
            break;
        }
       
        if (b == false) break;
    }
}
template<typename T>
void wybor2(Graf<T>* GRAF){
    int nowy;
    cout << "ustal liczbe wierzcholkow: " << endl;
    cin >> nowy;
    GRAF->set_Vnum(nowy);
   
    cout << "ustal gestosc grafu: " << endl;
    cin >> nowy;
    GRAF->set_Density(nowy);
   
    cout << "podaj wierzcholek startowy" << endl;
    cout << "zakres od 0 do " << GRAF->return_V_num() << endl;
    cin >> nowy;
    GRAF->set_Start(nowy);
    GRAF->Generate_Graf();
    GRAF->List_to_Matrix();
    cout << "\n graf zapisano do pliku \n";
    int wybor;
    bool b = true;
    while (true) {
      
        cout << "Wybierz opcje: " << endl
            << "1 \t" << "wyswietl tablice sasiedztwa\t \n"
            << "2 \t" << "wyswietl macierz\t \n"
            << "3 \t" << "znajdz droge dla obecnego grafu (na liscie)\t \n"
            << "4 \t" << "znajdz droge dla obecnego grafu (na macierzy)\t \n"
            << "5 \t" << "pokaz droge oraz koszta\t \n"
            << "6 \t" << "zmien wierzcholek startowy\t \n"
            << "0 \t" << "- zakoncz - \t \n";
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            GRAF->print_List();
            cin.get();
            break;
        case 2:
            GRAF->print_Matrix();
            cin.get();
            break;
        case 3:
            GRAF->BF_for_list();
            cout << "znaleziono" << endl;
            break;
        case 4:
            GRAF->BF_for_matrix();
            cout << "znaleziono" << endl;
            break;
        case 5:
            GRAF->print_Cost();
            GRAF->write_Patch();
            cout << "\n sciezke zapisano do pliku \n";
            cin.get();
            break;
        case 6:
            cout << "zakres od 0 do " << GRAF->return_V_num() << endl;
            cin >> nowy;
            GRAF->set_Start(nowy);
            break;
        case 0:
            b = false;
            break;
        default:
            break;
        }
      
        if (b == false) break;
    }
}

int main(){
    srand(time(0));
                             
   
    Graf<DT> GRAF;
    GRAF.set_Start(0);
    GRAF.set_Vnum(10);
    GRAF.set_Density(50);
    int wybor;
    while (true) {
        cout << string(50, '\n');
        cout << "Wybierz opcje: " << endl
            << "1 \t"<<"wczytaj graf\t \n"
            << "2 \t" << "generuj graf\t \n"
            << "3 \t" << "WYKONAJ TEST - PROJEKT2 \t \n"
            << "0 \t" << "- zakoncz - \t \n";
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            wybor1(&GRAF);
            break;
        case 2:
            wybor2(&GRAF);
            break;
        case 3:
            GRAF.test();
            break;
        case 0:
            return 0;
            break;
        default:
            break;
        }
        cout << string(50, '\n');
    } 


return 0;
}
