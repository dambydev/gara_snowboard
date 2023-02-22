/*!
    \file  main.cpp
    \brief Simulatore di gare di kayt-snowboard
    \author D'Ambrosio Davide
    \date 21/02/2023
*/
#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;
/*
 Traccia
 C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder.
 Dopo mezz'ora termina la registrazione. All'interno di un file sono elencati matricola, cognome e coordinate rilevate.
 Realizzare un software in C++ che mi indichi il podio vincente,
 tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.
 (Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100)
 */

/*struct competitor{
    int matricola, x, y, distance;
    string cog;
};*/

class competitor{
    public:
    int x, y, distance;
    string cog, matricola;
};

competitor(){

}

void full_vet(list<competitor> vet){
    ifstream fin("list.txt", ios::in);
    if(!fin)
        cout<<"Errore di apertura del file";
    string app;
    int q;
    int i = 0;
    while(!fin.eof()){
        if(i != 4) {
            competitor c;
            getline(fin, app, ';');
            switch(i){
                case 0:
                    c.matricola = app;
                    break;
                case 1:
                    app.erase
                    c.cog = app;
                    break;
                case 2:
                    q = stoi(app);
                    c.x = q;
                    break;
                case 3:
                    q = stoi(app);
                    c.y = q;
                    break;
            }
            i++;
        }
        else{
            getline(fin, app, ';');
        }
    }
}

void new_race(){
    ifstream fin("list.txt", ios::in);
    if(!fin)
        cout<<"Errore di apertura del file";
    list<competitor> vet;
    full_vet(vet);
}

void res_out(){

}

void menu()
{
    int sc;
    do {
        cout << endl;
        cout << "------------------- MENU' -------------------" << endl;
        cout << "1 - Inizia gara nuova" << endl
             << "2 - Visualizza risultato" << endl
             << "3 - Uscita" << endl << endl
             << "Inserire scelta >> ";
        cin >> sc;
        switch (sc)
        {
            case 1:
                new_race();
                break;
            case 2:
                res_out();
                break;
            case 3:
                cout<<endl<<"Uscita..."<<endl;
                break;
            default:
                cout << endl << "Scelta sbagliata" << endl << endl;
        }
    } while (sc != 3);
}

int main()
{
    menu();
    return 0;
}
