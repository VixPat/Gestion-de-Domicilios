#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "Estructuras\Listas_Dobles.h"
#include <string>
#include <iostream>
using namespace std;

//Archivo include de la clase; Se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h

class Restaurante {
private:
    string codigo;
    string nombre;
    string zona_id;
    ListaDoble<string>* menu;

public:
    Restaurante(string codigo, string nombre, string zona_id);
    ~Restaurante();

    string getCodigo();
    string getNombre();
    string getZonaId();
    ListaDoble<string>* getMenu();

    void agregarPlato(string plato);
    bool tienePlato(string plato);
    void mostrarMenu();

    void mostrarInfo();

    bool operator<(const Restaurante& otro) const {
        return codigo < otro.codigo;
    }
    bool operator>(const Restaurante& otro) const {
        return codigo > otro.codigo;
    }
    bool operator==(const Restaurante& otro) const {
        return codigo == otro.codigo;
    }

    friend ostream& operator<<(ostream& os, const Restaurante* r) {
        os << r->codigo << " - " << r->nombre << " (Zona: " << r->zona_id << ")";
        return os;
    }
};

#endif //RESTAURANTE_H