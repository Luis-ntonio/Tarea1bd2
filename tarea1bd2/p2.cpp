//
// Created by lagg on 30/03/2022.
//


#include <iostream>
#include <fstream>
#include <vector>
#include<climits>
#include <cstring>

using namespace std;


void passingdata(char* val1, int tam){
    bool C = true;
    for (int i = 0; i < tam ; i++){

        if(val1[i] && C){
            continue;

        }
        else{
            val1[i] = ' ';
            C = false;
        }
    }
}
class header{
    int pos = -1;
public:
    void setpos(int _pos){
        pos = _pos;
    }
    int getpos() const{
        return pos;
    }
};
class Alumno{
    char Codigo [5];
    char Nombre [11];
    char Apellidos [20];
    char Carrera [15];
    int ciclo;
    float mensualidad;
    int verificar;
public:
    void SetData(){
        cin>>Codigo;
        cin>>Nombre;
        cin>>Apellidos;
        cin>>Carrera;
        cin>>ciclo;
        cin>>mensualidad;
        verificar = 0;
        passingdata(Codigo,5);
        passingdata(Nombre,11);
        passingdata(Apellidos,20);
        passingdata(Carrera,15);
    }
    int getciclo() {
        return this->ciclo;
    }
    float getmensualidad(){
        return mensualidad;
    }
    int getverificar(){
        return verificar;
    }
    void setvariables(int cic,float mens, int ver){
        ciclo = cic;
        mensualidad = mens;
        verificar = ver;
    }
    void setvar(int var){
        verificar = var;
    }
    void ShowData(){
        cout<<Codigo<<Nombre<<Apellidos<<Carrera<<ciclo<<mensualidad<<endl;
    }
};

class FixedFile{
private:
    string name_file;
public:
    FixedFile(string archivo): name_file (archivo){};


    void add(Alumno record){
        ofstream file(this->name_file, ios::app | ios::binary);
        ifstream check(this->name_file, ios::in | ios::binary);
        Alumno temp;
        if (file.tellp() == 0){
            header head;
            file.write((char*) &head, sizeof(head));

            file.write((char*) &record, sizeof (record));

        }
        else {
            check.seekg(0,ios::beg);
            header aux;
            check.read((char*)&aux,sizeof(aux));
            if (aux.getpos()==-1){
                file.seekp(0, ios::end);
                file.write((char*) &record, sizeof (record));
            }
            else{
                check.seekg(0,ios::beg);
                check.seekg(aux.getpos() * sizeof(Alumno) + sizeof(aux), ios::beg);
                check.read((char*) &temp,sizeof(temp));
                file.seekp(0,ios::beg);
                file.seekp(aux.getpos() * sizeof(Alumno) + sizeof(header));
                file.write((char*) &record, sizeof(record));
                file.seekp(0,ios::beg);
                aux.setpos(temp.getverificar());
                file.write((char*) &aux,sizeof(header));
            }


        }

        file.close();
    }


    Alumno readRecord(int pos){
        ifstream file(this->name_file, ios::in | ios::binary);
        Alumno record;

        file.seekg(pos * sizeof(record) + sizeof(header), ios::beg);
        file.read((char*) &record , sizeof(record));

        if (record.getverificar() != 0){
            throw "no existe data";
        }
        file.close();
        return record;
    }
    vector<Alumno> load(){
        ifstream file(this->name_file, ios::in |ios::binary);
        vector<Alumno> aux;
        file.seekg(0,ios::beg);
        header temp;
        file.read((char*)&temp,sizeof(temp));

        file.seekg(sizeof(header) , ios::beg);
        while(!file.eof()){
            Alumno record;

            file.read((char*) &record, sizeof(record));
            if(!file.good()) break;
            if (record.getverificar() == 0){
                aux.push_back(record);
            }


        }
        file.close();
        return aux;
    }
    bool elim(int pos) {

        fstream file(this->name_file,ios::in | ios::binary | ios::out);

        Alumno record{};
        file.seekg(0,ios::beg);
        header elimi;
        file.read((char*) &elimi, sizeof(elimi));
        file.seekg(pos * sizeof(record) + sizeof(header), ios::beg);

        file.read((char*) &record, sizeof(record));

        file.seekp(pos * sizeof(record) + sizeof(header));
        record.setvar(elimi.getpos());
        file.write((char*) &record, sizeof (record));
        file.seekp(0, ios::beg);
        elimi.setpos(pos);
        file.write((char*) &elimi, sizeof (elimi));
        file.close();

        return true;
    }
};


int textoo() {
    cout << "ingrese nombre de archivo en .dat"<< endl;
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
    auto x = archivos.load();
    archivos.elim(0);
    auto y = archivos.load();


    return 0;
}