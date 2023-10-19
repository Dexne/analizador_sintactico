#ifndef MANEJADOR_H
#define MANEJADOR_H

#include "./includes.h"

class Manejador {
private:
    string nombre_archivo;
    fstream *archivo;
public:
    Manejador(string);
};

Manejador::Manejador(string nombre) {
    string linea, palabra;
    this->nombre_archivo = nombre;
    this->archivo = new fstream(this->nombre_archivo, ios::in);
    
    if (this->archivo->is_open()) {
        for (int f = -1; f<FILAS-1; f++) {
        
            getline((*archivo), linea);
            stringstream fila(linea);

            // exclude title column
            if (f == -1) continue;

            for (int c = -1; c<COLUMNAS; c++) {
                getline(fila, palabra, ',');

                // exclude index column
                if (c == -1) continue;
                
                if (palabra == "") reglasProduccion[f][c] = 0;
                // d-rules production 
                else if (palabra[0] == 'd') {
                    palabra.erase(palabra.begin());
                    reglasProduccion[f][c] = std::stoi(palabra.c_str());
                }
                // r-rules reduction
                else if (palabra[0] == 'r') {
                    palabra.erase(palabra.begin());
                    reglasReduccion[f][c] = -1 * std::stoi(palabra.c_str());
                }
                // only number
                else if (palabra[0] >= '0' and palabra[0] <= '9') {
                    reglasProduccion[f][c] = std::stoi(palabra.c_str());
                }
            }
        }
    }
}

#endif
