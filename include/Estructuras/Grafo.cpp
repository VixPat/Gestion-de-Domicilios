#include "../../include/Estructuras/Grafo.h"
#include "../../include/Estructuras\ColasConPrioridad.h"
#include <limits>
#include <iomanip>

Arista::Arista(Vertice* dest, float p) : destino(dest), peso(p), siguiente(nullptr) {}
ListaAdyacencia::ListaAdyacencia() : primera(nullptr), ultima(nullptr) {}
ListaAdyacencia::~ListaAdyacencia() {
    while (primera != nullptr) {
        Arista* temp = primera;
        primera = primera->siguiente;
        delete temp;
    }
}

bool ListaAdyacencia::esVacia() {
    return primera == nullptr;
}
bool ListaAdyacencia::buscarAdyacencia(Vertice* destino) {
    Arista* temp = primera;
    while (temp != nullptr) {
        if (temp->destino->dato == destino->dato) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}
void ListaAdyacencia::agregar(Vertice* destino, float peso) {
    if (!buscarAdyacencia(destino)) {
        agregarArista(new Arista(destino, peso));
    }
}
void ListaAdyacencia::agregarArista(Arista* nuevaArista) {
    if (esVacia()) {
        primera = nuevaArista;
        ultima = nuevaArista;
        return;
    }
    string dato = nuevaArista->destino->dato;
    // Insertar al inicio
    if (dato < primera->destino->dato) {
        nuevaArista->siguiente = primera;
        primera = nuevaArista;
        return;
    }
    // Insertar al final
    if (dato > ultima->destino->dato) {
        ultima->siguiente = nuevaArista;
        ultima = nuevaArista;
        return;
    }
    // Insertar en medio (para mantenerlo ordenado)
    Arista* temp = primera;
    while (temp->siguiente != nullptr && dato > temp->siguiente->destino->dato) {
        temp = temp->siguiente;
    }
    nuevaArista->siguiente = temp->siguiente;
    temp->siguiente = nuevaArista;
}
void ListaAdyacencia::eliminar(Vertice* destino) {
    if (esVacia()) return;
    if (primera->destino->dato == destino->dato) {
        Arista* temp = primera;
        primera = primera->siguiente;
        if (primera == nullptr) {
            ultima = nullptr;
        }
        delete temp;
        return;
    }
    Arista* temp = primera;
    while (temp->siguiente != nullptr && temp->siguiente->destino->dato != destino->dato) {
        temp = temp->siguiente;
    }
    if (temp->siguiente != nullptr) {
        Arista* aEliminar = temp->siguiente;
        temp->siguiente = temp->siguiente->siguiente;
        if (temp->siguiente == nullptr) {
            ultima = temp;
        }
        delete aEliminar;
    }
}

Vertice::Vertice(string d) : dato(d), siguiente(nullptr) {
    listaAdyacencia = new ListaAdyacencia();
}
Vertice::~Vertice() {
    delete listaAdyacencia;
}

Grafo::Grafo() : primero(nullptr), ultimo(nullptr) {}
Grafo::~Grafo() {
    while (primero != nullptr) {
        Vertice* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}
bool Grafo::esVacio() {
    return primero == nullptr;
}
Vertice* Grafo::buscarVertice(string dato) {
    Vertice* temp = primero;
    while (temp != nullptr) {
        if (temp->dato == dato) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return nullptr;
}
void Grafo::agregarVertice(string dato) {
    if (buscarVertice(dato) != nullptr) {
        return; // Ya existe
    }
    Vertice* nuevoVertice = new Vertice(dato);
    if (esVacio()) {
        primero = nuevoVertice;
        ultimo = nuevoVertice;
        return;
    }
    // Insertar al inicio
    if (dato < primero->dato) {
        nuevoVertice->siguiente = primero;
        primero = nuevoVertice;
        return;
    }
    // Insertar al final
    if (dato > ultimo->dato) {
        ultimo->siguiente = nuevoVertice;
        ultimo = nuevoVertice;
        return;
    }
    // Insertar en medio (ordenado)
    Vertice* temp = primero;
    while (temp->siguiente != nullptr && dato > temp->siguiente->dato) {
        temp = temp->siguiente;
    }
    nuevoVertice->siguiente = temp->siguiente;
    temp->siguiente = nuevoVertice;
}
void Grafo::agregarArista(string origen, string destino, float peso) {
    Vertice* vOrigen = buscarVertice(origen);
    Vertice* vDestino = buscarVertice(destino);
    if (vOrigen != nullptr && vDestino != nullptr) {
        vOrigen->listaAdyacencia->agregar(vDestino, peso);
    }
}
void Grafo::eliminarArista(string origen, string destino) {
    Vertice* vOrigen = buscarVertice(origen);
    Vertice* vDestino = buscarVertice(destino);
    
    if (vOrigen != nullptr && vDestino != nullptr) {
        vOrigen->listaAdyacencia->eliminar(vDestino);
    }
}
void Grafo::eliminarVertice(string dato) {
    if (esVacio()) return;
    Vertice* verticeBorrar = nullptr;
    if (primero->dato == dato) {
        verticeBorrar = primero;
        primero = primero->siguiente;
        if (primero == nullptr) {
            ultimo = nullptr;
        }
    } else {
        Vertice* temp = primero;
        while (temp->siguiente != nullptr && temp->siguiente->dato != dato) {
            temp = temp->siguiente;
        }
        
        if (temp->siguiente != nullptr) {
            verticeBorrar = temp->siguiente;
            temp->siguiente = temp->siguiente->siguiente;
            if (temp->siguiente == nullptr) {
                ultimo = temp;
            }
        }
    }
    if (verticeBorrar != nullptr) {
        // Eliminar aristas que apuntan a este vértice
        Vertice* temp = primero;
        while (temp != nullptr) {
            temp->listaAdyacencia->eliminar(verticeBorrar);
            temp = temp->siguiente;
        }
        delete verticeBorrar;
    }
}

// Grafo de Djkstra
map<string, float> Grafo::Dijkstra(string origen) {
    Vertice* vOrigen = buscarVertice(origen);
    if (vOrigen == nullptr) {
        return map<string, float>();
    }
    map<Vertice*, float> distancias;
    map<Vertice*, bool> visitados;
    // Inicializar distancias
    Vertice* temp = primero;
    while (temp != nullptr) {
        distancias[temp] = numeric_limits<float>::infinity();
        visitados[temp] = false;
        temp = temp->siguiente;
    }
    distancias[vOrigen] = 0.0f;
    ColaPrioridad<Vertice*> cola;
    cola.encolar(vOrigen, 0.0f);
    while (!cola.estaVacia()) {
        Vertice* actual = cola.desencolar();
        if (visitados[actual]) {
            continue;
        }
        visitados[actual] = true;
        // Relajar aristas
        Arista* aristaActual = actual->listaAdyacencia->getPrimera();
        while (aristaActual != nullptr) {
            if (!visitados[aristaActual->destino]) {
                float nuevaDistancia = distancias[actual] + aristaActual->peso;
                if (nuevaDistancia < distancias[aristaActual->destino]) {
                    distancias[aristaActual->destino] = nuevaDistancia;
                    cola.encolar(aristaActual->destino, nuevaDistancia);
                }
            }
            aristaActual = aristaActual->siguiente;
        }
    }
    // Convertir a map<string, float>
    map<string, float> resultado;
    for (auto& par : distancias) {
        resultado[par.first->dato] = par.second;
    }
    return resultado;
}

//Metodo especifico para el sistema
float Grafo::obtenerDistancia(string origen, string destino) {
    map<string, float> distancias = Dijkstra(origen);
    if (distancias.find(destino) != distancias.end()) {
        return distancias[destino];
    }
    return numeric_limits<float>::infinity(); // No hay ruta
}
void Grafo::mostrarDistanciasDijkstra(string origen) {
    map<string, float> distancias = Dijkstra(origen);
    cout << "\nDistancias desde " << origen << ": " << endl;
    for (auto& par : distancias) {
        cout << origen << " -> " << par.first << ": ";
        if (par.second == numeric_limits<float>::infinity()) {
            cout << "INF" << endl;
        } else {
            cout << par.second << " km" << endl;
        }
    }
}

// Esto es para obtener datos sobre los recoridos (TODO:Prob lo elimine, voy a ver si lo uso pa algo o no)
void Grafo::recorridoAnchura(string dato) {
    Vertice* vertice = buscarVertice(dato);
    if (vertice == nullptr) return;
    set<Vertice*> visitados;
    Cola<Vertice*> cola;
    visitados.insert(vertice);
    cola.enqueue(vertice);
    cout << "Recorrido en Anchura desde " << dato << ": ";
    while (cola.getSize() > 0) {
        Vertice* actual = cola.dequeue();
        cout << actual->dato << " ";
        Arista* arista = actual->listaAdyacencia->getPrimera();
        while (arista != nullptr) {
            if (visitados.find(arista->destino) == visitados.end()) {
                visitados.insert(arista->destino);
                cola.enqueue(arista->destino);
            }
            arista = arista->siguiente;
        }
    }
    cout << endl;
}
void Grafo::recorridoProfundidad(string dato) {
    Vertice* vertice = buscarVertice(dato);
    if (vertice == nullptr) return;
    set<Vertice*> visitados;
    cout << "Recorrido en Profundidad desde " << dato << ": ";
    recorridoProfundidadRec(vertice, visitados);
    cout << endl;
}
void Grafo::recorridoProfundidadRec(Vertice* vertice, set<Vertice*>& visitados) {
    cout << vertice->dato << " ";
    visitados.insert(vertice);
    Arista* arista = vertice->listaAdyacencia->getPrimera();
    while (arista != nullptr) {
        if (visitados.find(arista->destino) == visitados.end()) {
            recorridoProfundidadRec(arista->destino, visitados);
        }
        arista = arista->siguiente;
    }
}