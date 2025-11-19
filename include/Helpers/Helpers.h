#ifndef HELPERS_H
#define HELPERS_H

#include "../Cliente.h"
#include "../Domiciliario.h"
#include "../Restaurante.h"
#include "../Pedido.h"
#include "../Zona.h"
#include "../Estructuras/Listas_Dobles.h"
#include "../Estructuras/Colas.h"
#include "../Estructuras/Pilas.h"
#include "../Estructuras/ABB.h"
#include "../Estructuras/Grafo.h"

//Archivo include de la clase; Se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h

Cliente* buscarCliente(ListaDoble<Cliente*>* clientes, string codigo);
Domiciliario* buscarDomiciliario(ListaDoble<Domiciliario*>* domiciliarios, string codigo);
Restaurante* buscarRestaurante(ArbolBB<Restaurante*>* restaurantes, string codigo);
Zona* buscarZona(ListaDoble<Zona*>* zonas, string id);
Pedido* buscarPedido(Cola<Pedido*>* pedidos, string id);

float calcularDistancia(Grafo* mapa, string zona1_id, string zona2_id); //Ya se usa un grafo, magnific
Domiciliario* buscarDomiciliarioDisponible(ListaDoble<Domiciliario*>* domiciliarios,
                                            Grafo* mapa,
                                            string zona_restaurante);

void crearPedido(ListaDoble<Cliente*>* clientes,
                 ArbolBB<Restaurante*>* restaurantes,
                 Cola<Pedido*>* pedidos_activos,
                 Pila<string>* historial_acciones);
void procesarSiguientePedido(Cola<Pedido*>* pedidos_activos,
                              ListaDoble<Domiciliario*>* domiciliarios,
                              Grafo* mapa,
                              ArbolBB<Restaurante*>* restaurantes);
void entregarPedido(Cola<Pedido*>* pedidos_activos,
                    ListaDoble<Pedido*>* pedidos_entregados,
                    ListaDoble<Domiciliario*>* domiciliarios,
                    ListaDoble<Cliente*>* clientes);
void cancelarUltimoPedido(Pila<string>* historial_acciones,
                          Cola<Pedido*>* pedidos_activos,
                          ListaDoble<Domiciliario*>* domiciliarios);

void mostrarRestaurantes(ArbolBB<Restaurante*>* restaurantes);
void mostrarRestauranteConMenu(ArbolBB<Restaurante*>* restaurantes, string codigo);
void mostrarPedidosActivos(Cola<Pedido*>* pedidos_activos);
void mostrarDomiciliarios(ListaDoble<Domiciliario*>* domiciliarios);
void verHistorialCliente(ListaDoble<Cliente*>* clientes);

void recorrerListaClientes(ListaDoble<Cliente*>* clientes);

void mostrarMapaCiudad(Grafo* mapa);

#endif //HELPERS_H