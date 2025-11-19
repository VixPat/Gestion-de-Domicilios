#ifndef ZONA_H
#define ZONA_H

#include <string>
#include <iostream>
using namespace std;

//Archivo include de la clase; Se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h
//18/11/25: Elimine Listas Circulares, mantuve to lo q pude pero lo modifique para q usara el Grafo y no la lista

class Zona {
private:
    string id;
    string nombre;

public:
    Zona(string id, string nombre);
    ~Zona();

    string getId();
    string getNombre();

    void mostrarInfo();
};
//Quiero dejar en claro q aca lit no se hicieron modificaciones, solo se elimino lo q ya no se usaba

#endif //ZONA_H