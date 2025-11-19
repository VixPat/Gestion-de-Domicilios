#ifndef COLASCONPRIORIDAD_H
#define COLASCONPRIORIDAD_H

#include <iostream>
#include <functional>
using namespace std;

template <typename T>
struct NodoColaPrioridad {
    T dato;
    float prioridad;
    NodoColaPrioridad<T>* siguiente;

    NodoColaPrioridad(T valor, float p) : dato(valor), prioridad(p), siguiente(nullptr) {}
};

template <typename T>
class ColaPrioridad {
private:
    NodoColaPrioridad<T>* head;
    int size;
public:
    ColaPrioridad() : head(nullptr), size(0) {}

    ~ColaPrioridad() {
        while (head != nullptr) {
            NodoColaPrioridad<T>* temp = head;
            head = head->siguiente;
            delete temp;
        }
    }
    // Encolar con prioridad (menor prioridad = sale primero)
    void encolar(T dato, float prioridad) {
        NodoColaPrioridad<T>* nuevo = new NodoColaPrioridad<T>(dato, prioridad);

        // Si está vacía o tiene mayor prioridad que el head
        if (head == nullptr || prioridad < head->prioridad) {
            nuevo->siguiente = head;
            head = nuevo;
        } else {
            // Buscar posición correcta
            NodoColaPrioridad<T>* temp = head;
            while (temp->siguiente != nullptr && temp->siguiente->prioridad <= prioridad) {
                temp = temp->siguiente;
            }
            nuevo->siguiente = temp->siguiente;
            temp->siguiente = nuevo;
        }
        size++;
    }
    // Desencolar (sacar el de menor prioridad)
    T desencolar() {
        if (head == nullptr) {
            throw runtime_error("Cola de prioridad vacia");
        }
        NodoColaPrioridad<T>* temp = head;
        T dato = temp->dato;
        head = head->siguiente;
        delete temp;
        size--;
        return dato;
    }
    // Ver el frente sin sacar
    T verFrente() {
        if (head == nullptr) {
            throw runtime_error("Cola de prioridad vacia");
        }
        return head->dato;
    }
    // Verificar si está vacía
    bool estaVacia() {
        return head == nullptr;
    }
    // Obtener tamaño
    int getSize() {
        return size;
    }
    // Mostrar (para debug)
    void mostrar() {
        NodoColaPrioridad<T>* temp = head;
        cout << "Cola Prioridad: ";
        while (temp != nullptr) {
            cout << "(" << temp->dato << ":" << temp->prioridad << ") -> ";
            temp = temp->siguiente;
        }
        cout << "NULL" << endl;
    }
};

#endif //COLASCONPRIORIDAD_H