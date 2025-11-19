#ifndef ABB_H
#define ABB_H

#include <iostream>
using namespace std;

//Estructura de Arbol Binario de Busqueda

template <typename T>
struct NodoABB {
    T dato;
    NodoABB<T>* left;
    NodoABB<T>* right;
    NodoABB(T valor) : dato(valor), left(nullptr), right(nullptr) {}
};

template <typename T>
class ArbolBB {
private:
    NodoABB<T>* root = nullptr;

    void insertarRec(NodoABB<T>*& nodo, T valor) {
        if (nodo == nullptr) {
            nodo = new NodoABB<T>(valor);
        } else if (valor < nodo->dato) {
            insertarRec(nodo->left, valor);
        } else if (valor > nodo->dato) {
            insertarRec(nodo->right, valor);
        } else {
            cout << "Elemento duplicado\n";
        }
    }
    void inOrdenRec(NodoABB<T>* nodo) {
        if (nodo != nullptr) {
            inOrdenRec(nodo->left);
            cout << nodo->dato << " ";
            inOrdenRec(nodo->right);
        }
    }
    NodoABB<T>* buscarRec(NodoABB<T>* nodo, T valor) {
        if (nodo == nullptr || nodo->dato == valor) {
            return nodo;
        } else if (valor < nodo->dato) {
            return buscarRec(nodo->left, valor);
        } else {
            return buscarRec(nodo->right, valor);
        }
    }
    NodoABB<T>* buscarMin(NodoABB<T>* nodo) {
        while (nodo != nullptr && nodo->left != nullptr) {
            nodo = nodo->left;
        }
        return nodo;
    }
    NodoABB<T>* eliminarRec(NodoABB<T>* nodo, T valor) {
        if (nodo == nullptr) {
            cout << "Elemento no encontrado\n";
            return nodo;
        }
        if (valor < nodo->dato) {
            nodo->left = eliminarRec(nodo->left, valor);
        } else if (valor > nodo->dato) {
            nodo->right = eliminarRec(nodo->right, valor);
        } else {
            if (nodo->left == nullptr && nodo->right == nullptr) {
                delete nodo;
                nodo = nullptr;
            }
            else if (nodo->left == nullptr) {
                NodoABB<T>* temp = nodo;
                nodo = nodo->right;
                delete temp;
            }
            else if (nodo->right == nullptr) {
                NodoABB<T>* temp = nodo;
                nodo = nodo->left;
                delete temp;
            }
            else {
                NodoABB<T>* temp = buscarMin(nodo->right);
                nodo->dato = temp->dato;
                nodo->right = eliminarRec(nodo->right, temp->dato);
            }
        }
        return nodo;
    }
    void limpiarRec(NodoABB<T>* nodo) {
        if (nodo != nullptr) {
            limpiarRec(nodo->left);
            limpiarRec(nodo->right);
            delete nodo;
        }
    }

public:
    ArbolBB() = default;
    ~ArbolBB() {
        limpiarRec(root);
        root = nullptr;
    }
    //Metodo para insertar datos a la lista
    void insertar(T valor) {
        insertarRec(root, valor);
    }
    //Metodo para mostrar los datos de la lista in-order
    void inOrden() {
        inOrdenRec(root);
        cout << "NULL\n";
    }
    //Metodo para devolver un dato que se requiera
    NodoABB<T>* buscarYRetornar(T valor) {
        return buscarRec(root, valor);
    }
    //Getter
    NodoABB<T>* getRoot() {
        return root;
    }
};

#endif //ABB_H