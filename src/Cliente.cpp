#include "../include/Cliente.h"

//Constructor y Destructor de la Clase
Cliente::Cliente(string codigo, string nombre, string zona_id, string telefono) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->zona_id = zona_id;
    this->telefono = telefono;
    this->historial_pedidos = new Pila<string>();
}
Cliente::~Cliente() {
    delete historial_pedidos; //Limpieza de Memoria
}

//Metodos "getters", son para acceder a informacion privada (atributos) de forma publica
string Cliente::getCodigo() {
    return codigo; //Codigo unico del cliente
}
string Cliente::getNombre() {
    return nombre; //Nombre del cliente
}
string Cliente::getZonaId() {
    return zona_id; //Zona en la q se encuentra
}
string Cliente::getTelefono() {
    return telefono; //Celular
}
Pila<string>* Cliente::getHistorial() {
    return historial_pedidos; //Para ver su historial (Del cliente especifico, se usa el codigo)
}

//Metodos de trabajo de la clase
void Cliente::agregarAlHistorial(string pedido_id) {
    historial_pedidos->push(pedido_id);
    //El pedido (ya registrado en una lista) se agrega al historial (que es otra lista :])
}
void Cliente::verHistorial() {
    //Para ver el historial total de cierto cliente
    cout << "\n_ Historial de Pedidos de " << nombre << " (Mas recientes primero) _" << endl;
    if (historial_pedidos->getSize() == 0) {
        cout << "No hay pedidos en el historial." << endl;
    } else {
        historial_pedidos->show();
    }
}

//Muestra la informacion total del cliente
void Cliente::mostrarInfo() {
    cout << "\n_ Informacion del Cliente _" << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Zona: " << zona_id << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Total de pedidos: " << historial_pedidos->getSize() << endl;
}