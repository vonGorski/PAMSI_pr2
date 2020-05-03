#include "Graf.h"




#define RANGE  10  // zakres wartowsci wag 
#define LOOPS 100  // ile wykonan algorytmu testu

template<typename T>
void Graf<T>::destro_matrix() {
    for (int i = 0; i < V_num; i++) { delete[] MATRIX[i]; }
    delete[] MATRIX;
    MATRIX = NULL;
}

template<typename T>
void Graf<T>::destro_list() {
    for (int i = 0; i < V_num; i++) {
        NList<T>* pt;
        NListE<T>* p;
        pt = &VTAB[i];
        p = pt->front;
        // zapamiêtujemy pocz¹tek
        if (p)
        {
            pt->front = p->next; // nowy pocz¹tek
            delete p;    // usuñ element z pamiêci
        }
    }
    delete[] VTAB;
}

template<typename T>
void Graf<T>::print_Matrix() {
    T max = std::numeric_limits<T>::max();  // maksymalna wartosc dla danego typu
    for (int i = 0; i < V_num; i++)
    {
        for (int j = 0; j < V_num; j++) {
            if (MATRIX[i][j] == max) cout << " --\t";
            else cout << " " << MATRIX[i][j] << "\t";
        }
        cout << endl;
    }

}

template<typename T>
void Graf<T>::print_List() {
    for (int i = 0; i < V_num; i++)
    {

        NList<T>* pnl = &VTAB[i];
        cout << "V#" << i << endl;
        pnl->print();
    }
}

template<typename T>
void Graf<T>::print_Cost() {
    int* S = new int[V_num];    // Tworzymy prosty stos
    int sptr = 0;

    for (int i = 0; i < V_num; i++)
    {
        cout << i << ": ";
        for (int j = i;j != -1;j = Previous[j]) // Wierzcho³ki œcie¿ki umieszczamy na stosie
            S[sptr++] = j; // w kolejnoœci od ostatniego do pierwszego

        while (sptr)       // Wierzcho³ki ze stosu drukujemy
            cout << S[--sptr] << " "; // w kolejnoœci od pierwszego do ostatniego

        cout << "koszt " << Cost[i] << "\t" << endl; // Na koñcu wyœwietlamy koszt
    }
    delete[] S;         // Usuwamy stos
}

template<typename T>
void Graf<T>::Generate_Graf() {  // tworzy graf na liscie
    VTAB = new NList<T>[V_num];  // tworzymy dynamiczna tablice list
    int  num_of_neighbors;
    if (Density == 100) num_of_neighbors = ((V_num * Density) / 100) - 1;
    else num_of_neighbors = ((V_num * Density) / 100);
    edge_number = V_num * num_of_neighbors;
    for (int i = 0; i < V_num; i++) {         // dla kazdego wierzcholka


        NList<T>* pnl = &VTAB[i];                       //wskaznik na dana liste sasiedztwa


        NListE<T>* r = new NListE<T>;              // tutaj tworzy sie sciezke miedzy nastepnymi wierzcholkami zeby nie powstal las
        if (i == V_num - 1)   r->v = 0;
        else                 r->v = i + 1;
        r->w = (rand() % RANGE) + 1;                     // +1 zeby uniknac zerowej wagi
        pnl->push_front(r);


        list<int> l_of_previous; // lista juz istniejacych polaczen
        l_of_previous.push_front(i);   //zeby nie bylo petli z wierzcholka a do a
        l_of_previous.push_front(i + 1);   // umieszcza nastepny wierzcholkek(ten tworzacy sciezke laczaca wszystkie)
        for (int j = 0; j < num_of_neighbors - 1; j++) { // num -1 zeby stworzyc jedna sciezke laczaca wszystkich
            NListE<T>* p = new NListE<T>;



            int vnew = rand() % V_num;  // nowy wierzcholek

            while (true) // petla sprawdza liste dotychczasowych saisadow i generuje nowego siasiada nie nalezacego do niej
            {
                bool b = true;
                for (int k : l_of_previous) {
                    if (vnew == k) { vnew = rand() % V_num;b = true; break; }
                    else  b = false;
                }
                if (b == false) break;
            }

            p->v = vnew;
            p->w = (rand() % RANGE) + 1;                   //+1 zeby uniknac zerowej wagi
            pnl->push_front(p);
            l_of_previous.push_front(vnew);
        }


    }
    //   print_List(); // kontrola
}

template<typename T>
void Graf<T>::List_to_Matrix() {
    // generowanie tablicy wype³nionej maxem
    T max = std::numeric_limits<T>::max();  // maksymalna wartosc dla danego typu
    MATRIX = new int* [V_num];
    for (int i = 0; i < V_num; i++) {
        MATRIX[i] = new int[V_num];
    }
    // ustawianie wag na max dla kazdego pola (domyslnie gdy nie ma krawedzi)
    // 0 dla samego siebie 
    for (int i = 0; i < V_num; i++) {
        for (int j = 0; j < V_num; j++) {
            MATRIX[i][j] = max;
            if (j == i) { MATRIX[i][j] = 0; }
        }
    }

    NListE<T>* pv;
    int a;
    for (int i = 0; i < V_num; i++) {
        NList<T>* pvL = &VTAB[i];
        for (pv = pvL->front; pv; pv = pv->next)
        {
            a = pv->v;
            MATRIX[i][a] = pv->w;
        }

    }
    //  print_Matrix(); kontrola
}

template<typename T>
void Graf<T>::BF_for_list() {
    Cost = new T[V_num];   // tablica kosztow
    Previous = new int[V_num];  //tablica numerow poprzednikow

    T max = std::numeric_limits<T>::max();  // maksymalna wartosc dla danego typu

    for (int i = 0; i < V_num; i++) {
        Cost[i] = max;           // dla pozostalych nieskonczonosc
    }

    Cost[start] = 0;   // dla wierzcholka startowego 0

    for (int i = 0; i < V_num; i++) {
        Previous[i] = -1;
    }

    //bool test;
    NListE<T>* pv;
    for (int i = 1; i < V_num; i++)   // Pêtla relaksacji
    {

        for (int j = 0; j < V_num; j++) { // Przechodzimy przez kolejne wierzcho³ki grafu
           // test = true;
            NList<T>* pvL = &VTAB[j];
            for (pv = pvL->front; pv; pv = pv->next) { // Przegl¹damy listê s¹siadów wierzcho³ka x
                if (Cost[pv->v] > Cost[j] + pv->w) // Sprawdzamy warunek relaksacji
                {
                    // test = false;
                    Cost[pv->v] = Cost[j] + pv->w; // Relaksujemy krawêdŸ z x do jego s¹siada
                    Previous[pv->v] = j;   // Poprzednikiem s¹siada bêdzie x

                }
            }
            // if (test) break;
        }
    }

}

template<typename T>
void Graf<T>::BF_for_matrix() {
    Cost = new T[V_num];   // tablica kosztow
    Previous = new int[V_num];  //tablica numerow poprzednikow

    T max = std::numeric_limits<T>::max();  // maksymalna wartosc dla danego typu

    for (int i = 0; i < V_num; i++) {
        Cost[i] = max;           // dla pozostalych nieskonczonosc
    }

    Cost[start] = 0;   // dla wierzcholka startowego 0

    for (int i = 0; i < V_num; i++) {
        Previous[i] = -1;
    }

    //  bool test;
    for (int i = 1; i < V_num; i++)
    {
        //  test = true;
        for (int j = 0; j < V_num; j++)
        {
            for (int k = 0; k < V_num; k++)
            {
                if (Cost[j] != max && MATRIX[j][k] != max && MATRIX[k][j] != 0 && Cost[k] > Cost[j] + MATRIX[j][k]) {
                    // test = false;
                    Cost[k] = Cost[j] + MATRIX[j][k];
                    Previous[k] = j;
                }
            }
        }
        // if (test) break;
    }

}

template<typename T>
void Graf<T>::write_Generated() {
    fstream oput;
    oput.open("dane.txt", ios_base::out);

    oput << edge_number << " " << V_num << " " << start << endl;  // zapis podstawowych danych
    NListE<T>* pv;
    for (int i = 0; i < V_num;i++) {
        NList<T>* pnl = &VTAB[i];
        for (pv = pnl->front; pv; pv = pv->next) {
            oput << i << " " << pv->v << " " << pv->w << endl;
        }

    }
}

template<typename T>
void Graf<T>::write_Patch() { // kalka print_cost
    fstream oput;
    oput.open("sciezka.txt", ios_base::out);
    int* S = new int[V_num];
    int sptr = 0;

    for (int i = 0; i < V_num; i++)
    {
        oput << i << ": ";
        for (int j = i;j != -1;j = Previous[j])
            S[sptr++] = j;

        while (sptr)
            oput << S[--sptr] << " ";

        oput << "koszt " << Cost[i] << "\t" << endl;
    }
    delete[] S;
}

template<typename T>
void Graf<T>::read_from_file() {
    ifstream iput;
    iput.open("dane.txt", ios_base::in);
    iput >> edge_number >> V_num >> start;  // zapis podstawowych danych
    VTAB = new NList<T>[V_num];  // tworzy liste list
    int nu, nv;
    T  nw;
    NList<T>* pnl;

    for (int i = 0; i < edge_number; i++) {
        iput >> nu;
        pnl = &VTAB[nu];
        iput >> nv >> nw;
        NListE<T>* p = new NListE<T>;

        p->v = nv;
        p->w = nw;
        pnl->push_front(p);

    }
}

template<typename T>
void Graf<T>::test() {
    int den_tab[4] = { 25, 50, 75, 100 };  //tablica gestosci
    int size[5] = { 100, 200, 500, 750, 1000 }; //tablica rozmiarow

    std::ofstream file1("PomiaryL.txt");
    std::ofstream file2("PomiaryM.txt");
    float time, time1 = 0, time2 = 0;
    for (int i = 0; i < 4; i++) { // petla gestosci
        set_Density(den_tab[i]);
        for (int j = 0; j < 5; j++) {


            time1 = 0;
            time2 = 0;
            for (int k = 0; k < LOOPS; k++) {
                set_Vnum(size[j]);
                Generate_Graf();
                List_to_Matrix();

                auto start = std::chrono::steady_clock::now();

                BF_for_list();

                auto end = std::chrono::steady_clock::now();

                destro_list();
               
                std::chrono::duration<double> elapsed_seconds = end - start;
                time = elapsed_seconds.count();
                time1 += time;


                start = std::chrono::steady_clock::now();

                BF_for_matrix();

                end = std::chrono::steady_clock::now();

                destro_matrix();

                elapsed_seconds = end - start;
                time = elapsed_seconds.count();
                time2 += time;


           }
            file1 << time1 << "\n"; //elapsed_seconds.count() << "\n";
            std::cout << "list " << den_tab[i] << "% " << "size:" << size[j] << " elapsed time: " << time1 << "s\n";
            file2 << time2 << "\n";//elapsed_seconds.count() << "\n" << "\n";
            std::cout << "matrix " << den_tab[i] << "% " << "size:" << size[j] << " elapsed time: " << time2 << "s\n";
        }
        file1 << "\n";
        file2 << "\n";

    }
    // file.close();
}
