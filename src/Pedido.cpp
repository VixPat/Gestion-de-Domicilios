#include "../include/Pedido.h"

Pedido::Pedido(string id, string cliente_codigo, string zona_destino_id) {
    this->id = id;
    this->cliente_codigo = cliente_codigo;
    this->zona_destino_id = zona_destino_id;
    this->estado = "PENDIENTE";
    this->restaurante_codigo = "";
    this->domiciliario_codigo = "";
    this->items = new ListaDoble<string>();
}
Pedido::~Pedido() {
    delete items;
}
//Getters
string Pedido::getId() {
    return id;
}
string Pedido::getClienteCodigo() {
    return cliente_codigo;
}
string Pedido::getRestauranteCodigo() {
    return restaurante_codigo;
}
string Pedido::getDomiciliarioCodigo() {
    return domiciliario_codigo;
}
string Pedido::getEstado() {
    return estado;
}
string Pedido::getZonaDestino() {
    return zona_destino_id;
}
ListaDoble<string>* Pedido::getItems() {
    return items;
}
//Metodo para añadir un item al pedido (Este se verifica junto con "tienePlato" q mencione antes, en los metodos auxiliares)
void Pedido::agregarItem(string item) {
    items->insertTail(item);
    cout << "Item agregado al pedido: " << item << endl;
}
//Metodo para asignar un restaurante
//Esto en realidad lo escoje el usuario x la consola pero este metodo es para actualizar la info de forma mas automatica
void Pedido::asignarRestaurante(string restaurante_codigo) {
    this->restaurante_codigo = restaurante_codigo;
    cout << "Restaurante asignado: " << restaurante_codigo << endl;
}
//Aca si que se define en automatico, cuando se ve quien es el mejor Domi (eso se define en los metodo auxiliares)
//Pues se asigna el domi con este metodo y se actualiza la info
void Pedido::asignarDomiciliario(string domiciliario_codigo) {
    this->domiciliario_codigo = domiciliario_codigo;
    this->estado = "EN_CAMINO";
    cout << "Domiciliario asignado: " << domiciliario_codigo << endl;
}
//Metodo general para cambiar el estado en las diversas etapas del sistema
//(Ya sea que se entrege, se cancele o se tenga en camino)
void Pedido::cambiarEstado(string nuevo_estado) {
    if (estado != nuevo_estado) {
        cout << "[INFO] Estado del pedido: " << estado << " -> " << nuevo_estado << endl;
    }
    estado = nuevo_estado;
}
//para mostrar la info
void Pedido::mostrarInfo() {
    cout << "\n_ Pedido #" << id << " ===" << endl;
    cout << "Cliente: " << cliente_codigo << endl;
    cout << "Zona destino: " << zona_destino_id << endl;
    cout << "Estado: " << estado << endl;
    if (restaurante_codigo != "") {
        cout << "Restaurante: " << restaurante_codigo << endl;
    }
    if (domiciliario_codigo != "") {
        cout << "Domiciliario: " << domiciliario_codigo << endl;
    }
    cout << "\nItems del pedido:" << endl;
    if (items->getSize() == 0) {
        cout << "  (vacio)" << endl;
    } else {
        items->goHeadToTail();
    }
}