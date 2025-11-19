#include "../include/Restaurante.h"
#include "../include/Estructuras/Listas_Dobles.h"

//Constructor y Destructor (No creo q sea necesario especificar eso, dejare de hacerlo)
Restaurante::Restaurante(string codigo, string nombre, string zona_id) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->zona_id = zona_id;
    this->menu = new ListaDoble<string>();
}
Restaurante::~Restaurante() {
    delete menu;//Limpiar memoria
}
//Getters
string Restaurante::getCodigo() {
    return codigo;
}
string Restaurante::getNombre() {
    return nombre;
}
string Restaurante::getZonaId() {
    return zona_id;
}
ListaDoble<string>* Restaurante::getMenu() {
    return menu;
}
//Metodo para agregar platos al menu de X restaurante
void Restaurante::agregarPlato(string plato) {
    menu->insertTail(plato);
    cout << "Plato agregado: " << plato << endl;
}
//Metodo para verificar si el plato que se ingreso esta en el menu
//Esto se usa cuando se va a pedir un pedido y se tiene q ingresar el nombre x consola
//Es sensible a Mayusculas y Minusculas, ojo con eso
bool Restaurante::tienePlato(string plato) {
    NodoListaDoble<string>* temp = menu->getHead();
    while (temp != nullptr) {
        if (temp->dato == plato) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
//Metodo para ver el menu completo del restaurante
void Restaurante::mostrarMenu() {
    cout << "\n_ Menu de " << nombre << " _" << endl;
    if (menu->getSize() == 0) {
        cout << "El menu esta vacio." << endl;
    } else {
        menu->goHeadToTail();
    }
}
//Para ver la info del restaurante
void Restaurante::mostrarInfo() {
    cout << "\n_ Informacion del Restaurante _" << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Zona: " << zona_id << endl;
    cout << "Total de platos en menu: " << menu->getSize() << endl;
}