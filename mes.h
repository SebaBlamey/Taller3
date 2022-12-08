#pragma once
#include <iostream>

using namespace std;

class mes{
    private:
        string nombre;
        int peso;
    public:
        mes(string nombre,int peso){
            this->nombre = nombre;
            this->peso = peso;
        }
        string imprimir(){
            cout << "Mes: " << nombre << "Pesos: " << peso << endl; 
        }
        
};
