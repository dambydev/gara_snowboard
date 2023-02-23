/*!
    \file  main.cpp
    \brief Simulatore di gare di kayt-snowboard
    \author D'Ambrosio Davide
    \date 21/02/2023
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
/*
 Traccia
 C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder.
 Dopo mezz'ora termina la registrazione. All'interno di un file sono elencati matricola, cognome e coordinate rilevate.
 Realizzare un software in C++ che mi indichi il podio vincente,
 tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.
 (Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100)
 */

struct competitor{
    int matricola, x, y, distance;
    string cog;
};

void write_original_file(vector<competitor> vet){
    ofstream fout("list.txt");
    fout<<"";
        for(int i=0; i<vet.size(); i++){
            fout<<vet.at(i).matricola<<"; ";
            fout<<vet.at(i).cog<<"; ";
            fout<<'0'<<"; ";
            fout<<'0'<<"; ";
            if(i != vet.size()-1)
                fout<<'0'<<";"<<'\n';
            else
                fout<<'0'<<";";
            }
}

void write_file(vector<competitor> vet, vector<competitor> podio){
    ofstream fout("list.txt");
    fout<<"";
    for(int i=0; i<podio.size(); i++){
        fout<<podio.at(i).matricola<<"; ";
        fout<<podio.at(i).cog<<"; ";
        fout<<podio.at(i).x<<"; ";
        fout<<podio.at(i).y<<"; ";
        fout<<podio.at(i).distance<<";"<<'\n';
    }
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
                    app.erase(remove(app.begin(),app.end(),' '),app.end());
                    stringstream(app) >> q;
                    c.x = q;
                    break;
                case 3:
                    app.erase(remove(app.begin(),app.end(),' '),app.end());
                    stringstream(app) >> q;
                    c.y = q;
                    break;
                case 4:
                    app.erase(remove(app.begin(),app.end(),' '),app.end());
                    stringstream(app) >> q;
                    c.distance = q;
                    vet.push_back(c);
                    cont = true;
                    break;
            }
            i++;
        }
    }
    vet.erase(vet.begin()+vet.size()-1);
}

int first(vector<competitor> vet){
    int k;
    for (int i = 0; i < vet.size(); i++){
        if(i==0) {
            if (vet.at(i).distance > vet.at(i + 1).distance)
                k = i;
            else
                k = i+1;
            i++;
        }
        else{
            if(vet.at(k).distance<vet.at(i).distance)
                k = i;
        }
    }
    return k;
}

void generate_position(vector<competitor>& vet){
    for(int q = 0; q<30; q++) {
        for (int i = 0; i < vet.size(); i++) {
            int x1 = vet.at(i).x;
            int y1 = vet.at(i).y;
            vet.at(i).x = rand() % 101;
            vet.at(i).y = rand() % 101;
            vet.at(i).distance = vet.at(i).distance + sqrt((y1 - vet.at(i).y) * (y1 - vet.at(i).y) + (x1 - vet.at(i).x) * (x1 - vet.at(i).x));
        }
    }
}

void podium(vector<competitor> vet){
    vector<competitor> podio;
    for(int i=0; i<3; i++){
        competitor c = vet.at(first(vet));
        vet.erase(vet.begin()+first(vet));
        podio.push_back(c);
        cout<<endl<<"Al "<<i+1<<" posto abbiamo: "<<podio.at(i).cog<<" con una distanza percorsa di "<<podio.at(i).distance<<endl;
    }
    write_file(vet, podio);
}

void new_race(vector<competitor>& vet){
    ifstream fin("list.txt");
    if(!fin)
        cout<<"Errore di apertura del file";
    vet.clear();
    full_vet(vet);
    write_original_file(vet);
    generate_position(vet);
    cout<<endl<<"La gara e' iniziata!"<<endl;
}

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

void menu()
{
    int sc;
    vector<competitor> vet;
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
                new_race(vet);
                break;
            case 2:
                podium(vet);
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

int main()
{
    srand(time(NULL));
    menu();
    return 0;
}
