#include "../include/Zona.h"
//Blah blah blah
Zona::Zona(string id, string nombre) {
    this->id = id;
    this->nombre = nombre;
}
Zona::~Zona() {
    //No hay memoria dinamica q liberar
}
//Getters
string Zona::getId() {
    return id;
}
string Zona::getNombre() {
    return nombre;
}
/*
TODO Iba a eliminar todo esto pero decidi dejarlo para tener claridad de lo q se hizo antes
ListaCircular<string>* Zona::getVecinos() {
    return vecinos;
}
Metodo para "agregar un vecino" a X zona
Si revisamos la DB vemos que los tenemos ubicacion x codigo R001 hasta R005 y cada uno tiene su ubicacion
Este metodo lo que hace es que registrar las conexiones entre las zonas
Se conecta el id de la zona y la distancia (Ej: Z001:5, como se ve en la DB), eso es lo q insertamos en la lista de vecinos
Aunq se pone al inicio pues sigue siendo una lista circular sin orden, solo se añade un nuevo nodo, cumpliendo su rol de lista de adyacencia.
TODO: Era este (Ya no se usa pero lo voy a dejar aca para no tener q borrar todo)
TODO: void Zona::agregarVecino(string zona_id, int distancia) {
    string dato = zona_id + ":" + to_string(distancia);
    vecinos->insertFirst(dato);
    cout << "Vecino agregado: " << zona_id << " (" << distancia << " km)" << endl;
}
Metodo para encontrar distancia entre vecinos, sí si es vecino de la zona especifica
Osea recorre la lista y la descompone para obtener el id (Ej: Z001:5, pues agarraria el Z001)
Si el id q se obtiene es el q se esta buscando, pues agarra la distancia (Z001:5, agarra 5) y lo retorna
TODO: int Zona::getDistanciaAVecino(string zona_id) {
    if (vecinos->getSize() == 0) return -1;
    NodoListaCircular<string>* temp = vecinos->getHead();
    if (temp == nullptr) return -1;
    do {
        // Separar "zona_id:distancia"
        string dato = temp->dato;
        int pos = dato.find(":");
        string id = dato.substr(0, pos);
        if (id == zona_id) {
            string dist = dato.substr(pos + 1);
            return stoi(dist);
        }
        temp = temp->next;
    } while (temp != vecinos->getHead());
    return -1;
}
Metodo para ver si una zona es vecina de otra zona, retorna true si son vecino, si no, no
TODO: bool Zona::esVecino(string zona_id) {
    if (vecinos->getSize() == 0) return false;
    string buscar = zona_id + ":";
    NodoListaCircular<string>* temp = vecinos->getHead();
    if (temp == nullptr) return false;
    do {
        if (temp->dato.find(buscar) == 0) {
            return true;
        }
        temp = temp->next;
    } while (temp != vecinos->getHead());
    return false;
}
//Metodo q recibe una zona y muestra sus vecinos
TODO: void Zona::mostrarVecinos() {
    cout << "\nVecinos de " << nombre << ":" << endl;
    if (vecinos->getSize() == 0) {
        cout << "No tiene vecinos" << endl;
    } else {
        vecinos->Run();
    }
}
*/
//Ver la info, tmb voy a dejar de explicar eso
void Zona::mostrarInfo() {
cout << "\n_ Zona _" << endl;
cout << "ID: " << id << endl;
cout << "Nombre: " << nombre << endl;
}