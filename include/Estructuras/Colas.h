#ifndef COLAS_H
#define COLAS_H

#include <iostream>
using namespace std;

//Estructura de Cola

template <typename T>
struct NodoColas{
    T dato;
    NodoColas<T> *next = nullptr;
    NodoColas(T valor) : dato(valor) {}
};

template <typename T>
class Cola {
private:
    NodoColas<T> *head = nullptr;
    NodoColas<T> *tail = nullptr;
    int size = 0;

public:
    Cola() = default;
    ~Cola(){
        while (head != nullptr){
            NodoColas<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
    };
    //Metodo para añadir datos a la cola (Se ponen de ultimos)
    void enqueue(T dato){
        NodoColas<T> *nuevoNodo = new NodoColas<T>(dato);
        if( head == nullptr ){
            head = tail = nuevoNodo;
        } else {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
        }
        size++;
    }
    //Metodo para sacar datos de la cola (Salen los primeros)
    T dequeue(){
        if (head == nullptr) return T();
        NodoColas<T> *tmp = head;
        T dato = tmp->dato;
        head = head->next;
        if( head == nullptr ) tail = nullptr;
        size--;
        delete tmp;
        return dato;
    }
    //Metodo para ver el tamaño total de la Cola (Osea para saber cuantos elementos hay)
    int getSize(){ return size; }
    void show(){
        NodoColas<T> *tmp = head;
        while (tmp != nullptr){
            cout << tmp->dato << " -> ";
            tmp = tmp->next;
        }
        cout << "NULL" << endl;
    }
    //Metodo para saber cual es el primer elemento en la cola
    NodoColas<T>* getNodoHead() {
        return head;
    }
    //Plantilla de Predicado
    //Es decir, una función que devuelve bool (true o false)
    template<typename Pred>
    //Metodo que "rompe la cola" y elimina datos sin seguir el orden, siempre y cuando cumpla el requisito
    bool removeIf(Pred predicate) {
        if (head == nullptr) return false;
        NodoColas<T>* temp = head;
        NodoColas<T>* prev = nullptr;
        while (temp != nullptr) {
            if (predicate(temp->dato)) {
                if (prev == nullptr) {
                    head = head->next;
                } else {
                    prev->next = temp->next;
                }
                if (temp == tail) {
                    tail = prev;
                }
                NodoColas<T>* aEliminar = temp;
                temp = temp->next;
                delete aEliminar;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }
};

#endif //COLAS_H