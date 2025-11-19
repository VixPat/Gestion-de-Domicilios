#ifndef PILAS_H
#define PILAS_H

#include <iostream>
using namespace std;

template <typename T>
struct NodoPila{
    T dato;
    NodoPila<T> *next = nullptr;
    NodoPila(T valor) : dato(valor) {}
};

template <typename T>
class Pila {
private:
    NodoPila<T> *top = nullptr;
    int size = 0;

public:
    Pila() = default;
    ~Pila(){
        while (top != nullptr){
            NodoPila<T> *tmp = top;
            top = top->next;
            delete tmp;
        }
    };
    //Para añadir un dato (Ya me canse de comentar)
    void push(T dato){
        NodoPila<T> *nuevoNodo = new NodoPila<T>(dato);
        nuevoNodo->next = top;
        top = nuevoNodo;
        size++;
    }
    //Para eliminar
    T pop(){
        if (top == nullptr) return T();
        NodoPila<T> *tmp = top;
        T dato = tmp->dato;
        top = top->next;
        size--;
        delete tmp;
        return dato;
    }
    //Para ver quien esta de primero (en la cima de la pila)
    T getTop(){
        if( top == nullptr ) return T();
        return top->dato;
    }
    //Para saber el tamaño
    int getSize(){ return size; }
    void show(){
        NodoPila<T> *tmp = top;
        while (tmp != nullptr){
            cout << tmp->dato << " -> ";
            tmp = tmp->next;
        }
        cout << "NULL" << endl;
    }
};

#endif //PILAS_H