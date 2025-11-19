#ifndef CLIENTE_H
#define CLIENTE_H

#include "Estructuras\Pilas.h"
#include <iostream>
#include <string>
using namespace std;

//Archivo include del cliente, se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h

class Cliente {
private:
    string codigo;
    string nombre;
    string zona_id;
    string telefono;
    Pila<string>* historial_pedidos;

public:
    Cliente(string codigo, string nombre, string zona_id, string telefono);
    ~Cliente();

    string getCodigo();
    string getNombre();
    string getZonaId();
    string getTelefono();
    Pila<string>* getHistorial();

    void agregarAlHistorial(string pedido_id);
    void verHistorial();

    void mostrarInfo();
};

#endif //CLIENTE_H