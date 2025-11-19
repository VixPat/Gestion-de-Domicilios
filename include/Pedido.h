#ifndef PEDIDO_H
#define PEDIDO_H

#include "Estructuras\Listas_Dobles.h"
#include <string>
using namespace std;

//Archivo include de la clase; Se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h

class Pedido {
private:
    string id;
    string cliente_codigo;
    string restaurante_codigo;
    string domiciliario_codigo;
    ListaDoble<string>* items;
    string estado;
    string zona_destino_id;

public:
    Pedido(string id, string cliente_codigo, string zona_destino_id);
    ~Pedido();

    string getId();
    string getClienteCodigo();
    string getRestauranteCodigo();
    string getDomiciliarioCodigo();
    string getEstado();
    string getZonaDestino();
    ListaDoble<string>* getItems();

    void agregarItem(string item);

    void asignarRestaurante(string restaurante_codigo);
    void asignarDomiciliario(string domiciliario_codigo);

    void cambiarEstado(string nuevo_estado);

    void mostrarInfo();
};

#endif //PEDIDO_H