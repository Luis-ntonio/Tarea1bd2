//
// Created by lagg on 30/03/2022.
//


#include <iostream>
#include <fstream>
#include <vector>
#include<climits>
#include <cstring>

using namespace std;



void readFromConsole(char buffer[], int size){
    string temp;
    cin >> temp;
    for(int i=0; i<size; i++)
        buffer[i] = (i < temp.size())? temp[i] : ' ';
    buffer[size-1] = '\0';
    cin.clear();
}
class Alumno{
public:
    char Codigo [6];
    char Nombre [12];
    char Apellidos [21];
    char Carrera [16];
    void SetData(){
        readFromConsole(Codigo,6);
        readFromConsole(Nombre,12);
        readFromConsole(Apellidos,21);
        readFromConsole(Carrera,16)
        ;
    }
    void ShowData(){
        cout<<Codigo;
        cout<<Nombre;
        cout<<Apellidos;
        cout<<Carrera;
        cout<<endl;
    }
    char* getcodigo(){
        return Codigo;
    }
};
ostream & operator << (ostream & stream, Alumno & p)
{
    stream << p.Codigo;
    stream << p.Nombre;
    stream << p.Apellidos;
    stream<< p.Carrera;
    stream << "\n";
    stream << flush;
    return stream;
}
istream & operator >> (istream & stream, Alumno & p)
{
    stream.get(p.Codigo, 5+1);
    stream.get(p.Nombre, 11+1);
    stream.get(p.Apellidos, 20+1);
    stream.get(p.Carrera, 15+1);
    stream.get();
    return stream;
}
class FixedFile{
private:
    string name_file;
public:
    FixedFile(string archivo): name_file (archivo){};


    void add(Alumno record){
        ofstream file(this->name_file, ios::app);

        file<<record;
        file.close();
    }
    Alumno readRecord(int pos){
        ifstream file(this->name_file);
        Alumno record;
        file.seekg(pos * sizeof(record) - 3*pos, ios::beg);
        file>>record;
        file.close();
        return record;
    }
    vector<Alumno> load(){
        ifstream file(this->name_file);
        vector<Alumno> aux;
        Alumno record{};
        while(!file.eof()){
            record = Alumno();
            file>>record;

            if(!file.good()) break;
            aux.push_back(record);

        }
        file.close();
        return aux;
    }
};

int textoo() {
    cout << "ingrese nombre de archivo"<< endl;
    string archivo;
    cin>> archivo;
    FixedFile archivos{archivo};
    cout << "ingrese numero de datos"<< endl;
    int cant=0;
    cin>>cant;
    for (int i = 0; i < cant; ++i) {
        Alumno aux;
        aux.SetData();
        archivos.add(aux);
    }

    auto x = archivos.readRecord(0);
    x.ShowData();
    return 0;
}