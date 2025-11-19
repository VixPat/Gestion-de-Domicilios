#ifndef TESTS_H
#define TESTS_H

#include "../include/Cliente.h"
#include "../include/Domiciliario.h"
#include "../include/Restaurante.h"
#include "../include/Pedido.h"
#include "../include/Zona.h"
#include "../include/Estructuras/Listas_Dobles.h"
#include "../include/Estructuras/Colas.h"
#include "../include/Estructuras/Pilas.h"
#include "../include/Estructuras/ABB.h"
#include "../include/Estructuras/Grafo.h"
#include "../include/Helpers/Helpers.h"
#include "../include/DB/DB.h"

#include <iostream>
using namespace std;

void test_flujo_completo_exitoso(ListaDoble<Zona*>* zonas,
                                   ListaDoble<Domiciliario*>* domiciliarios,
                                   ArbolBB<Restaurante*>* restaurantes,
                                   ListaDoble<Cliente*>* clientes,
                                   Cola<Pedido*>* pedidos_activos,
                                   Pila<string>* historial_acciones,
                                   ListaDoble<Pedido*>* pedidos_entregados,
                                   Grafo* mapa);

void test_manejo_errores(ListaDoble<Zona*>* zonas,
                         ListaDoble<Domiciliario*>* domiciliarios,
                         ArbolBB<Restaurante*>* restaurantes,
                         ListaDoble<Cliente*>* clientes,
                         Cola<Pedido*>* pedidos_activos,
                         Pila<string>* historial_acciones,
                         ListaDoble<Pedido*>* pedidos_entregados,
                         Grafo* mapa);

void test_estructuras_y_concurrencia(ListaDoble<Zona*>* zonas,
                                      ListaDoble<Domiciliario*>* domiciliarios,
                                      ArbolBB<Restaurante*>* restaurantes,
                                      ListaDoble<Cliente*>* clientes,
                                      Cola<Pedido*>* pedidos_activos,
                                      Pila<string>* historial_acciones,
                                      ListaDoble<Pedido*>* pedidos_entregados,
                                      Grafo* mapa);

#endif