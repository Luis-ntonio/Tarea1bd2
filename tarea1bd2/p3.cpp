//
// Created by lagg on 30/03/2022.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include<climits>
#include <cstring>
#include <sstream>

using namespace std;


class Alumno{
    string Nombre ;
    string Apellidos ;
    string Carrera ;
    float mensualidad;
public:
    void setdatos(string a, string b, string c, float d){
        Nombre = std::move(a);
        Apellidos = std::move(b);
        Carrera = std::move(c);
        mensualidad = d;
    }
    void SetData(string cadena = ""){
        if (cadena == "") {
            cin >> cadena;
        }
        vector<string>aux;
        int start = 0;
        int end = 0;
        for(int i = 0; i < 3; i++){
            end = cadena.find('|',start);
            aux.push_back(cadena.substr(start, end-start));
            start = end + 1;
        }
        auto x = cadena.substr(start,*(cadena.end()-1));
        auto y = stof(x);
        setdatos(aux[0],aux[1],aux[2],y);
    }
    void ShowData(){
        cout<<Nombre<< ' ' <<Apellidos<< ' ' <<Carrera<< ' ' << mensualidad<<endl;
    }
    float getcodigo(){
        return mensualidad;
    }
    string getnombre(){
        return Nombre;
    }
    string getapellido(){
        return Apellidos;
    }
    string getcarrera(){
        return Carrera;
    }

};


class VariableRecord{
private:
    string name_file;
public:
    VariableRecord(string archivo): name_file (archivo){};
    void add(Alumno record){
        ofstream file(this->name_file, ios::app);
        if(!file.is_open()) throw "no se pudo abrir el archive";
        file<<record.getnombre()<<'|'<<record.getapellido()<<'|'<<record.getcarrera()<<'|' <<record.getcodigo();
        file<<"\n";
        file<<flush;
        file.close();
    }
    Alumno readRecord(int pos){
        ifstream file(this->name_file);
        Alumno record;
        string lines;
        file.seekg(pos * sizeof(record) , ios::beg);
        getline(file,lines);
        record.SetData(lines);
        file.close();
        return record;
    }
    vector<Alumno> load(){
        ifstream file(this->name_file, ios::in);
        vector<Alumno> aux;
        string leido;
        while(getline(file,leido)){
            Alumno record;


            record.SetData(leido);
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
    VariableRecord archivos{archivo};
    Alumno aux;
    cout << "ingrese numero de datos"<< endl;
    int cant=0;
    cin>>cant;
    for (int i = 0; i < cant; ++i) {
        Alumno aux;
        aux.SetData();
        archivos.add(aux);
    }
    auto x =archivos.load();

    for(auto i : x){
        i.ShowData();
    }
    return 0;
}