/*!
    \file  main.cpp
    \brief Simulatore di gare di kayt-snowboard
    \author D'Ambrosio Davide
    \date 21/02/2023
    \version 1.0
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;
/*! \mainpage DESCRIZIONE
 Traccia \n
 C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder.\n
 Dopo mezz'ora termina la registrazione. All'interno di un file sono elencati matricola, cognome e coordinate rilevate.\n
 Realizzare un software in C++ che mi indichi il podio vincente,
 tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.\n
 Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100.\n
 */

//! \brief Struttura del competitore
struct competitor{
    int matricola, x, y, distance;
    string cog;
};

/*!
    \fn write_original_file
    \param[in] vet Vettore contenente tutti i competitori
    \param[in] write Variabile per capire se la funzione deve resettare il file o scrivere i dati aggiornati
    \brief Metodo che serve ad aggiornare o resettare il filez
*/
void write_original_file(vector<competitor> vet, bool write){
    ofstream fout("list.txt");
    fout<<"";
    if(!write) {
        for (int i = 0; i < vet.size(); i++) {
            fout << vet.at(i).matricola << "; ";
            fout << vet.at(i).cog << "; ";
            fout << '0' << "; ";
            fout << '0' << "; ";
            if (i != vet.size() - 1)
                fout << '0' << ";" << '\n';
            else
                fout << '0' << ";";
        }
    }
    else{
        for(int i=0; i<vet.size(); i++){
            fout<<vet.at(i).matricola<<"; ";
            fout<<vet.at(i).cog<<"; ";
            fout<<vet.at(i).x<<"; ";
            fout<<vet.at(i).y<<"; ";
            if(i != vet.size()-1)
                fout<<vet.at(i).distance<<";"<<'\n';
            else
                fout<<vet.at(i).distance<<";";
        }
    }
}

/*!
    \fn full_vet
    \param[in] vet Vettore contenente tutti i competitori
    \brief Metodo che serve a riempire il vettore con i competitori
*/
void full_vet(vector<competitor>& vet){
    ifstream fin("list.txt");
    if(!fin)
        cout<<"Errore di apertura del file";
    string app;
    int q = 0;
    int i;
    bool cont = false;

    while(!fin.eof()){
        competitor c;
        i = 0;
        cont = false;
        while(!cont){
            getline(fin, app, ';');
            switch(i){
                case 0:
                    stringstream(app) >> q;
                    c.matricola = q;
                    break;
                case 1:
                    app.erase(remove(app.begin(),app.end(),' '),app.end());
                    c.cog = app;
                    break;
                case 2:
                    c.x = 0;
                    break;
                case 3:
                    c.y = 0;
                    break;
                case 4:
                    c.distance = 0;
                    vet.push_back(c);
                    cont = true;
                    break;
            }
            i++;
        }
    }
    vet.erase(vet.begin()+vet.size() - 1);
}

/*!
    \fn first
    \param[in] vet Vettore contenente tutti i competitori
    \brief Metodo che serve a decretare il primo posto tra i competitori contenuti nel vettore
    \result Puntatore alla posizione del vincitore nel vettore
*/
int first(vector<competitor> vet){
    int k;
    for (int i = 0; i < vet.size(); i++){
        if(i==0) {
            if (vet.at(i).distance > vet.at(i + 1).distance)
                k = i;
            else
                k = i + 1;
            i++;
        }
        else{
            if(vet.at(k).distance<vet.at(i).distance)
                k = i;
        }
    }
    return k;
}

/*!
   \fn distance
   \param[in] vet Vettore contenente tutti i competitori
   \param[in] i Puntatore agli elementi del vettore
   \param[in] x1 Posizione x precedente del competitore
   \param[in] y1 Posizione y precedente del competitore
   \brief Metodo che ritorna il valore della distanza percorsa
   \result Distanza percorsa
*/
int distance(vector<competitor>& vet, int i, int x1, int y1){
    return vet.at(i).distance + sqrt((y1 - vet.at(i).y) * (y1 - vet.at(i).y) + (x1 - vet.at(i).x) * (x1 - vet.at(i).x));
}

/*!
    \fn generate_position
    \param[in] vet Vettore contenente tutti i competitori
    \brief Metodo che serve a generare casualmente le posizioni x ed y per 30 volte
*/
void generate_position(vector<competitor>& vet){
    for(int q = 0; q<30; q++) {
        for (int i = 0; i < vet.size(); i++) {
            int x1 = vet.at(i).x;
            int y1 = vet.at(i).y;
            vet.at(i).x = rand() % 101;
            vet.at(i).y = rand() % 101;
            vet.at(i).distance = distance(vet, i, x1, y1);
        }
    }
}

/*!
    \fn podium
    \param[in] vet Vettore contenente tutti i competitori
    \param[in] start Variabile che indica se la gara è iniziata o meno
    \brief Metodo che serve a decretare il podio
*/
void podium(vector<competitor> vet, bool start){
    if(start) {
        vector<competitor> podio;
        for (int i = 0; i < 3; i++) {
            competitor c = vet.at(first(vet));
            vet.erase(vet.begin() + first(vet));
            podio.push_back(c);
            cout << endl << "Al " << i + 1 << " posto abbiamo: " << podio.at(i).cog << " con una distanza percorsa di "
                 << podio.at(i).distance << endl;
        }
    }
    else{
        cout<<endl<<"Devi iniziare una gara per vedere il podio!"<<endl;
    }
}

/*!
    \fn new_race
    \param[in] vet Vettore contenente tutti i competitori
    \param[in] start Variabile che indica se la gara è iniziata o meno
    \brief Metodo che serve a iniziare una nuova gara
*/
void new_race(vector<competitor>& vet, bool &start){
    ifstream fin("list.txt");
    if(!fin)
        cout<<"Errore di apertura del file";
    vet.clear();
    full_vet(vet);
    bool write = false;
    write_original_file(vet, write);
    generate_position(vet);
    cout<<endl<<"La gara e' iniziata!"<<endl;
    start = true;
}

void end_race(vector<competitor>& vet, bool &start){
    podium(vet, start);
    bool write = true;
    write_original_file(vet, write);
}

//! \brief Metodo che serve a stampare il file
void out_file(){
    ifstream fin("list.txt", ios::in);
    if(!fin)
        cout<<"Errore di apertura del file";
    string l;
    cout<<endl;
    while(!fin.eof()){
        getline(fin, l);
        cout<<l<<endl;
    }
}

//! \brief Metodo che mostra le opzioni possibili selezionabili
void menu()
{
    int sc;
    vector<competitor> vet;
    bool start = false;
    do {
        cout << endl;
        cout << "------------------- MENU' -------------------" << endl;
        cout << "1 - Inizia gara nuova" << endl
             << "2 - Visualizza risultato" << endl
             << "3 - Stampa file" << endl
             << "4 - Uscita" << endl << endl
             << "Inserire scelta >> ";
        cin >> sc;
        switch (sc)
        {
            case 1:
                new_race(vet, start);
                break;
            case 2:
                end_race(vet, start);
                break;
            case 3:
                out_file();
                break;
            case 4:
                cout<<endl<<"Uscita..."<<endl;
                break;
            default:
                cout << endl << "Scelta sbagliata" << endl << endl;
        }
    } while (sc != 4);
}

//! \brief Main
int main()
{
    srand(time(NULL));
    menu();
    return 0;
}
