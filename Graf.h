#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <list>                  //list - wykorzystywane jedsynie w trakcie generowania grafu 
#include <time.h>      // nie wplywa w zaden sposob na implementacje algorytmow ani struktur
#include <chrono>


using namespace std;


template<typename T>
struct NListE                                    // lista sasiedztwa  element
{
    int v;                                      // numer sasiada
    T w;                                        // waga krawedzi (zaleznie od problemu mozna nadac jej int, double), przykladowo dlugosc lotu
    NListE<T>* next;                            //=nullptr; // wskaznik na nastepny element (nastepnego sasiada)
   /* ~NListE() {
        if (next != NULL)
            delete next;
    }*/
};

template<typename T>
class NList                  // lista sasiedztwa pojedyncza
{
private:

public:
    NListE<T>* front, * back;
    unsigned counter;
    NList() // konstruktor
    {
        front = back = NULL; //ustawia glowe i ty³ na null
        counter = 0;  //licznik elementow na zero
    }

    ~NList() // destruktor
    {
        NListE<T>* p;

        while (front)
        {
            p = front->next;
            delete front;
            front = p;
        }
    }

    unsigned size()                 // zwraca dlugosc listy
    {
        return counter;
    }

    NListE<T>* push_front(NListE<T>* p) // Dodaje element na pocz¹tku listy i zwraca jego adres
    {
        p->next = front;
        front = p;
        if (!back) back = front;
        counter++;
        return front;
    }

    NListE<T>* push_back(NListE<T>* p) // Dodaje element na koñcu listy i zwraca jego adres
    {
        if (back) back->next = p;
        p->next = NULL;
        back = p;
        if (!front) front = back;
        counter++;
        return back;
    }

    void print()
    {
        NListE<T>* p;

        if (front == NULL) cout << "Lista jest pusta." << endl;
        else
        {
            p = front;
            while (p)
            {
                cout << p->v << " -numer sasiada " << p->w << " - waga" << endl;
                p = p->next;
            }
            cout << endl;
        }
    }
};

template<typename T>
class Graf {
private:
    NList<T>* VTAB; // wskaznik na tablice list
    int** MATRIX; // wskaznik na macierz
    int V_num; // ilosc wierzcholkow
    int Density; // gestosc grafu
    int edge_number; // ilosc krawedxzi
    int start; //wierzcholek startowy
    T* Cost;  // wskaznik na tablce kosztow
    int* Previous; // wskanik na tablice poprzednikow
public:
    ///**** dzia³ajace ****
    //// print
    void print_Matrix();
    void print_List();
    void print_Cost();
    /// dostep
    NList<T>* ReturnVTAB() { return VTAB; };
    int return_V_num() { return V_num; };
    void set_Vnum(int vnum) { V_num = vnum; };
    void set_Density(int den) { Density = den; };
    void set_Start(int star) { start = star; };
    /// generowanie i konwersje
    void Generate_Graf();  // tworzy graf na liscie
    void List_to_Matrix();
    /// algorytmy
    void BF_for_list();
    void BF_for_matrix();
    ///**** odczyt/zapis ****
    void write_Generated();
    void write_Patch();
    void  read_from_file();
    ///**** tstowanie ****
    void destro_list();
    void destro_matrix();
    void test();
};

template<typename T>
void Graf<T>::destro_matrix();

template<typename T>
void Graf<T>::destro_list();
template<typename T>
void Graf<T>::print_Matrix();
template<typename T>
void Graf<T>::print_List();
template<typename T>
void Graf<T>::print_Cost();
template<typename T>
void Graf<T>::Generate_Graf();
template<typename T>
void Graf<T>::List_to_Matrix();
template<typename T>
void Graf<T>::BF_for_list();
template<typename T>
void Graf<T>::BF_for_matrix();
template<typename T>
void Graf<T>::write_Generated();
template<typename T>
void Graf<T>::write_Patch();
template<typename T>
void Graf<T>::read_from_file();

template<typename T>
void Graf<T>::test();





#endif 