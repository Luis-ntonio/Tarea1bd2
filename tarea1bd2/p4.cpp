//
// Created by lagg on 30/03/2022.
//
#include<string>
#include <fstream>
#include <vector>

using namespace std;

//codigo incompleto diculpe

class Matricula
{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
public:
    Matricula() = default;
    void SetData(){
        cin>>codigo;
        cin>>ciclo;
        cin>>mensualidad;
        cin>>observaciones;
    }
    size_t tamcod(){
        size_t size = codigo.size();
        return size;
    }
    size_t tamobs(){
        size_t size = observaciones.size();
        return size;
    }
    string getcode(){
        return codigo;
    }
    int getciclo(){
        return ciclo;
    }
    float getmens(){
        return mensualidad;
    }
    string getobs(){
        return observaciones;
    }
    size_t tot(){
        size_t size = 0;
        size += sizeof(ciclo);
        size += sizeof(mensualidad);
        size += codigo.size() * sizeof(char);
        size += observaciones.size() * sizeof(char);
        return size;
    }
};


class VariableRecord{
private:
    string name_file;
public:
    explicit VariableRecord(string archivo): name_file (archivo){};
    void add(Matricula record){
        ofstream file(this->name_file, ios::app | ios::binary);

        size_t x = record.tamcod();
        file.write((char*) &x,sizeof(x));
        auto cod = record.getcode();
        file.write((char*) &cod[0],x);

        file<<record.getciclo();
        file<<record.getmens();

        size_t y = record.tamobs();
        file.write((char*) &y,sizeof(y));
        auto men = record.getobs();
        file.write((char*) &men[0], y);
        file.close();
    }
    string readRecord(int pos){
        ifstream file(this->name_file, ios::binary);
        Matricula record;
        string aux;
        size_t size;

        file.read((char*) &size,sizeof(size));
        aux.resize(size);
        file.read((char*) &aux[0], size);

        int op;
        file>>op;

        float ip;
        file>>ip;

        string aux2;
        size_t size2;

        file.read((char*) &size2,sizeof(size2));
        aux2.resize(size2);
        file.read((char*) &aux2[0], size2);


        file.close();
        return aux;
    }
    vector<Matricula> load(){
        ifstream file(this->name_file, ios::in | ios::binary);
        vector<Matricula> aux;
        /*while(!file.eof()){
            Matricula record;
            string lines;
            getline(file,lines);
            record.SetData(lines);
            file.get();
            if(!file.good()) break;
            aux.push_back(record);

        }*/
        file.close();
        return aux;
    }
};

int textoo() {
    cout << "ingrese nombre de archivo"<< endl;
    string archivo;
    cin>> archivo;
    VariableRecord archivos{archivo};
    Matricula aux;
    aux.SetData();
    archivos.add(aux);

    auto x = archivos.readRecord(0);
    cout<<x;
    // auto x =archivos.load();

    /* for(auto i : x){
         i.ShowData();
     }*/
    return 0;
}
