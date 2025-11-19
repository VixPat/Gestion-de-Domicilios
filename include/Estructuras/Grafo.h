#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <map>
#include <set>
#include <iostream>
#include "ColasConPrioridad.h"
#include "Colas.h"

using namespace std;

class Vertice;
class Arista;
class ListaAdyacencia;

class Arista {
public:
    Vertice* destino;
    float peso;
    Arista* siguiente;

    Arista(Vertice* dest, float p);
};

class ListaAdyacencia {
private:
    Arista* primera;
    Arista* ultima;

public:
    ListaAdyacencia();
    ~ListaAdyacencia();

    bool esVacia();
    bool buscarAdyacencia(Vertice* destino);
    void agregar(Vertice* destino, float peso);
    void agregarArista(Arista* nuevaArista);
    void eliminar(Vertice* destino);

    Arista* getPrimera() { return primera; }
};

class Vertice {
public:
    string dato;
    Vertice* siguiente;
    ListaAdyacencia* listaAdyacencia;

    Vertice(string d);
    ~Vertice();
};

class Grafo {
private:
    Vertice* primero;
    Vertice* ultimo;

    void recorridoProfundidadRec(Vertice* vertice, set<Vertice*>& visitados);

public:
    Grafo();
    ~Grafo();

    // Métodos de vértices
    void agregarVertice(string dato);
    void eliminarVertice(string dato);
    Vertice* buscarVertice(string dato);
    bool esVacio();
    // Métodos de aristas
    void agregarArista(string origen, string destino, float peso);
    void eliminarArista(string origen, string destino);
    // Recorridos
    void recorridoAnchura(string dato);
    void recorridoProfundidad(string dato);
    // Algoritmos de caminos más cortos
    map<string, float> Dijkstra(string origen);
    map<string, float> BellmanFord(string origen);
    map<string, map<string, float>> FloydWarshall();
    // Métodos de visualización
    void mostrarDistanciasDijkstra(string origen);
    void mostrarDistanciasBellmanFord(string origen);
    void mostrarDistanciasFloydWarshall();

    float obtenerDistancia(string origen, string destino);
};

#endif //GRAFO_H