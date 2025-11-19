#ifndef LISTAS_DOBLES_H
#define LISTAS_DOBLES_H

#include <iostream>
using namespace std;

template <typename T>
struct NodoListaDoble {
    T dato;
    NodoListaDoble<T>* prev;
    NodoListaDoble<T>* next;
    NodoListaDoble(T valor) : dato(valor), prev(nullptr), next(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    NodoListaDoble<T>* head = nullptr;
    NodoListaDoble<T>* tail = nullptr;
public:
    ListaDoble() = default;
    ~ListaDoble() {
        while (head != nullptr) {
            NodoListaDoble<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    };
    //Metodo para recorrer la lista empezando x la cabeza hasta la cola
    void goHeadToTail() {
        NodoListaDoble<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->dato << "\n";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    //Metodo para añadir un dato de primero en la lista
    void insertHead (T dato){
        NodoListaDoble<T>* newNode = new NodoListaDoble<T>(dato);
        if (head == nullptr) {
            head = newNode, tail = newNode;
        } else {
            newNode->next = head, head -> prev = newNode, head = newNode;
        }

    }
    //Lo apuesto al anterior, se añade de ultimo
    void insertTail (T dato) {
        NodoListaDoble<T>* newNode = new NodoListaDoble<T>(dato);
        if (head == nullptr) {
            head = newNode, tail = newNode;
        } else {
            newNode->prev = tail, tail -> next = newNode, tail = newNode;
        }
    }
    //Metodo para eliminar el primer elemento en lista
    void deleteHead() {
        if (head == nullptr) {
            cout << "Lista vacia\n";
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            NodoListaDoble<T>* temp = head;
            head = head -> next, head -> prev = nullptr;
            delete temp;
        }
    }
    //Lo mismo del anterior pero opuesto, elimina el ultimo
    void deleteTail(){
        if (head == nullptr) {
            cout << "Lista vacia\n";
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            NodoListaDoble<T>* temp = tail;
            tail = tail -> prev, tail -> next = nullptr;
            delete temp;
        }
    }
    //Metodo para eliminar un dato o elemento en especifico
    void deleteNode(T search){
        if (head == nullptr) {
            cout << "Lista vacia\n";
            return;
        }
        NodoListaDoble<T>* temp = head;
        while (temp != nullptr && temp->dato != search) {
            temp = temp -> next;
        } if (temp == nullptr) {
            cout << "Element not found\n";
            return;
        }
        if (temp == head) {
            head = head -> next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (temp == tail) {
            tail = tail -> prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
    }
    //Metodo para saber el tamaño de la lista, es decir, cuantos elementos hay
    int getSize() {
        int count = 0;
        NodoListaDoble<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    //Metodo para saber cual es el primer elemento en la lista
    NodoListaDoble<T>* getHead() {
        return head;
    }
};

#endif //LISTAS_DOBLES_H