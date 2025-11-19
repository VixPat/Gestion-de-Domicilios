#include "../../include/DB/DB.h"
#include <iostream>

using namespace std;

//Zonas preestablecidas del "Mapa"
//Se definen las zonas (5 en este caso), se define su ubicacion (Norte, Sur, Centro, etc.)
//y que tan lejos se encuentra la zona en específico de la ubicacion general
//Si se quieren agregan mas zonas se hace aca de forma manual, para añadirlas x consola, toca hacer el metodo lol

void DB::cargarZonas(ListaDoble<Zona*>* zonas) {
    cout << "Cargando zonas de la ciudad..." << endl;

    // Crear zonas (SIN usar el sistema de "vecinos" q se habia planeado antes)
    //Aca si q elimine ese codigo pq creo q solo con saber como funcionaban antes los metodos es mas q suficiente
    Zona* norte = new Zona("Z001", "Norte");
    Zona* sur = new Zona("Z002", "Sur");
    Zona* centro = new Zona("Z003", "Centro");
    Zona* este = new Zona("Z004", "Este");
    Zona* oeste = new Zona("Z005", "Oeste");

    zonas->insertTail(norte);
    zonas->insertTail(sur);
    zonas->insertTail(centro);
    zonas->insertTail(este);
    zonas->insertTail(oeste);

    cout << "5 zonas cargadas correctamente." << endl;
}

// Esto de aca si q es nuevo, añadimos las zonas al grafo para q las pueda leer
Grafo* DB::cargarGrafoZonas() {
    cout << "Construyendo mapa de la ciudad (Grafo)..." << endl;
    Grafo* mapa = new Grafo();
    // Agregar vértices (zonas)
    mapa->agregarVertice("Z001"); // Norte
    mapa->agregarVertice("Z002"); // Sur
    mapa->agregarVertice("Z003"); // Centro
    mapa->agregarVertice("Z004"); // Este
    mapa->agregarVertice("Z005"); // Oeste
    // Aristas bidireccionales (conexiones con distancias)
    // Norte ←→ Centro (5 km)
    mapa->agregarArista("Z001", "Z003", 5.0f);
    mapa->agregarArista("Z003", "Z001", 5.0f);
    // Norte ←→ Este (7 km)
    mapa->agregarArista("Z001", "Z004", 7.0f);
    mapa->agregarArista("Z004", "Z001", 7.0f);
    // Sur ←→ Centro (3 km)
    mapa->agregarArista("Z002", "Z003", 3.0f);
    mapa->agregarArista("Z003", "Z002", 3.0f);
    // Sur ←→ Oeste (6 km)
    mapa->agregarArista("Z002", "Z005", 6.0f);
    mapa->agregarArista("Z005", "Z002", 6.0f);
    // Centro ←→ Este (4 km)
    mapa->agregarArista("Z003", "Z004", 4.0f);
    mapa->agregarArista("Z004", "Z003", 4.0f);
    // Centro ←→ Oeste (6 km)
    mapa->agregarArista("Z003", "Z005", 6.0f);
    mapa->agregarArista("Z005", "Z003", 6.0f);

    cout << "Grafo construido: 5 zonas, 12 conexiones bidireccionales." << endl;
    return mapa;
}

//Metodo de carga para los Domi, funciona igual que el metodo anterior
//La difenrencia recae en que cuando un Domi cambia de zona (al entregar un pedido) su zona se actualiza
//Y la zona del pedido pasa a ser su Zona Actual

void DB::cargarDomiciliarios(ListaDoble<Domiciliario*>* domiciliarios) {
    cout << "Contratando domiciliarios..." << endl;

    Domiciliario* d1 = new Domiciliario("D001", "Juan Perez", "Z003", "moto");
    Domiciliario* d2 = new Domiciliario("D002", "Maria Garcia", "Z001", "bicicleta");
    Domiciliario* d3 = new Domiciliario("D003", "Carlos Lopez", "Z002", "carro");
    Domiciliario* d4 = new Domiciliario("D004", "Ana Martinez", "Z004", "moto");
    Domiciliario* d5 = new Domiciliario("D005", "Luis Rodriguez", "Z005", "bicicleta");

    domiciliarios->insertTail(d1);
    domiciliarios->insertTail(d2);
    domiciliarios->insertTail(d3);
    domiciliarios->insertTail(d4);
    domiciliarios->insertTail(d5);

    cout << "5 domiciliarios contratados." << endl;
}

//Metodo para la carga automatica de los Restaurantes y los Menu
//Aca los metodos son solo de carga, usando las estructuras (ABB y ListaDoble), es decir, estos no
//se modifican mas adelante, para añadir datos se tiene que hacer aca mismo de forma manual

void DB::cargarRestaurantes(ArbolBB<Restaurante*>* restaurantes) {
    cout << "Registrando restaurantes..." << endl;

    Restaurante* r1 = new Restaurante("R001", "Bella Italia", "Z003");
    r1->agregarPlato("Pizza Margarita");
    r1->agregarPlato("Pasta Carbonara");
    r1->agregarPlato("Lasagna");
    r1->agregarPlato("Tiramisu");
    restaurantes->insertar(r1);

    Restaurante* r2 = new Restaurante("R002", "Dragon Dorado", "Z001");
    r2->agregarPlato("Arroz Chino");
    r2->agregarPlato("Chop Suey");
    r2->agregarPlato("Wantan");
    r2->agregarPlato("Rollitos Primavera");
    restaurantes->insertar(r2);

    Restaurante* r3 = new Restaurante("R003", "Sweet Dreams", "Z004");
    r3->agregarPlato("Helado");
    r3->agregarPlato("Torta de Chocolate");
    r3->agregarPlato("Donas");
    r3->agregarPlato("Cupcakes");
    restaurantes->insertar(r3);

    Restaurante* r4 = new Restaurante("R004", "Sakura Sushi", "Z002");
    r4->agregarPlato("Sushi Variado");
    r4->agregarPlato("Ramen");
    r4->agregarPlato("Tempura");
    r4->agregarPlato("Mochi");
    restaurantes->insertar(r4);

    Restaurante* r5 = new Restaurante("R005", "Burger House", "Z005");
    r5->agregarPlato("Hamburguesa");
    r5->agregarPlato("Papas Fritas");
    r5->agregarPlato("Nuggets");
    r5->agregarPlato("Coca Cola");
    restaurantes->insertar(r5);

    cout << "5 restaurantes registrados." << endl;
}

//Hace falta el modulo de registro de clientes, estos se deberian poder actualizar de forma manual en la consola
//Pero aja, a modo de ejemplo ya se tienen 3 clientes cargados

void DB::cargarClientesEjemplo(ListaDoble<Cliente*>* clientes) {
    cout << "Registrando clientes de prueba..." << endl;

    Cliente* c1 = new Cliente("C001", "Pedro Sanchez", "Z001", "300-1234567");
    Cliente* c2 = new Cliente("C002", "Laura Torres", "Z003", "300-7654321");
    Cliente* c3 = new Cliente("C003", "Miguel Angel", "Z005", "310-1111111");

    clientes->insertTail(c1);
    clientes->insertTail(c2);
    clientes->insertTail(c3);

    cout << "3 clientes registrados." << endl;
}