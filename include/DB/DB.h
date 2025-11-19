#ifndef DB_H
#define DB_H

#include "../Cliente.h"
#include "../Domiciliario.h"
#include "../Restaurante.h"
#include "../Zona.h"
#include "../Estructuras/Listas_Dobles.h"
#include "../Estructuras/ABB.h"
#include "../Estructuras/Grafo.h"

//Clase tipo "Base de Datos" para no registrar entidades de forma manual
//(Como los menus de los restaurantes, domiciliarios, ect)

class DB {
public:
    void cargarZonas(ListaDoble<Zona*>* zonas);
    void cargarDomiciliarios(ListaDoble<Domiciliario*>* domiciliarios);
    void cargarRestaurantes(ArbolBB<Restaurante*>* restaurantes);
    void cargarClientesEjemplo(ListaDoble<Cliente*>* clientes);
    Grafo* cargarGrafoZonas();  //Añadí esto aca para no tener q leer un txt, ded igual modo los datos siempre se "almacenaron" en la "DataBase"
};

#endif //DB_H