#include "include/Cliente.h"
#include "include/Domiciliario.h"
#include "include/Restaurante.h"
#include "include/Pedido.h"
#include "include/Zona.h"
#include "include/DB/DB.h"
#include "include/Estructuras/Grafo.h"

#include "include/Estructuras/Listas_Dobles.h"
#include "include/Estructuras/Colas.h"
#include "include/Estructuras/Pilas.h"
#include "include/Estructuras/ABB.h"
#include "include/Helpers/Helpers.h"
#include "Tests/Test.h"

ListaDoble<Zona*>* zonas;
ListaDoble<Domiciliario*>* domiciliarios;
ArbolBB<Restaurante*>* restaurantes;
ListaDoble<Cliente*>* clientes;

Cola<Pedido*>* pedidos_activos;
Pila<string>* historial_acciones;
ListaDoble<Pedido*>* pedidos_entregados;
Grafo* mapa_ciudad;
//Llama lo que tiene que llamar y hace listas globales
//Funcion del menu, para modularizacion
//Eso no se muestra en consola, pero si pone en la opcion "100" va a permitir escojer entre 3 casos de pruebas automaticos

void mostrarMenu() {
    cout << "SISTEMA DE PEDIDOS A DOMICILIO" << endl;
    cout << "1.  Ver restaurantes disponibles" << endl;
    cout << "2.  Ver menu de un restaurante" << endl;
    cout << "3.  Crear nuevo pedido" << endl;
    cout << "4.  Procesar siguiente pedido" << endl;
    cout << "5.  Entregar pedido" << endl;
    cout << "6.  Cancelar ultimo pedido" << endl;
    cout << "7.  Ver pedidos activos" << endl;
    cout << "8.  Ver domiciliarios" << endl;
    cout << "9.  Ver historial de cliente" << endl;
    cout << "10. Ver clientes registrados" << endl;
    cout << "0.  Salir" << endl;
    cout << "________________________" << endl;
    cout << "Opcion: ";
}

int main() {

    //Carga las listas y activa la DB
    zonas = new ListaDoble<Zona*>();
    domiciliarios = new ListaDoble<Domiciliario*>();
    restaurantes = new ArbolBB<Restaurante*>();
    clientes = new ListaDoble<Cliente*>();

    pedidos_activos = new Cola<Pedido*>();
    historial_acciones = new Pila<string>();
    pedidos_entregados = new ListaDoble<Pedido*>();

    cout << "\n_ Cargando datos del sistema _" << endl;
    DB db;
    db.cargarZonas(zonas);
    db.cargarDomiciliarios(domiciliarios);
    db.cargarRestaurantes(restaurantes);
    db.cargarClientesEjemplo(clientes);
    mapa_ciudad = db.cargarGrafoZonas();

    cout << "\n[SISTEMA LISTO]" << endl;

    //Ahora si el ciclo que detecta la entrada de opciones del usuario por consola
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch(opcion) {
            case 1:
                mostrarRestaurantes(restaurantes);
                break;
            case 2: {
                string codigo;
                cout << "\nCodigo del restaurante: ";
                cin >> codigo;
                mostrarRestauranteConMenu(restaurantes, codigo);
                break;
            }
            case 3:
                crearPedido(clientes, restaurantes, pedidos_activos, historial_acciones);
                break;
            case 4:
                procesarSiguientePedido(pedidos_activos, domiciliarios, mapa_ciudad, restaurantes);
                break;
            case 5:
                entregarPedido(pedidos_activos, pedidos_entregados, domiciliarios, clientes);
                break;
            case 6:
                cancelarUltimoPedido(historial_acciones, pedidos_activos, domiciliarios);
                break;
            case 7:
                mostrarPedidosActivos(pedidos_activos);
                break;
            case 8:
                mostrarDomiciliarios(domiciliarios);
                break;
            case 9:
                verHistorialCliente(clientes);
                break;
            case 10:
                recorrerListaClientes(clientes);
                break;
            //Estos son los caso de prueba automaticos, no se muestran en el menu principal
            //Pero si en las opciones escribes 100, t va a mostrar las pruebas automaticas
            case 100: {
                cout << "Test Automaticos" << endl;
                cout << "1. Test 1: Flujo completo exitoso" << endl;
                cout << "2. Test 2: Manejo de errores" << endl;
                cout << "3. Test 3: Estructuras y concurrencia" << endl;
                cout << "4. Ejecutar todos los tests" << endl;
                cout << "0. Volver al menu principal" << endl;
                cout << "Selecciona un test: ";
                int test_opcion;
                cin >> test_opcion;
                switch(test_opcion) {
                    case 1:
                        test_flujo_completo_exitoso(zonas, domiciliarios, restaurantes,
                                                   clientes, pedidos_activos,
                                                   historial_acciones, pedidos_entregados,
                                                   mapa_ciudad);
                        break;
                    case 2:
                        test_manejo_errores(zonas, domiciliarios, restaurantes,
                                           clientes, pedidos_activos,
                                           historial_acciones, pedidos_entregados,
                                           mapa_ciudad);
                        break;
                    case 3:
                        test_estructuras_y_concurrencia(zonas, domiciliarios, restaurantes,
                                                       clientes, pedidos_activos,
                                                       historial_acciones, pedidos_entregados,
                                                       mapa_ciudad);
                        break;
                    case 4:
                        cout << "\n[EJECUTANDO TODOS LOS TESTS]\n" << endl;
                        test_flujo_completo_exitoso(zonas, domiciliarios, restaurantes,
                                                   clientes, pedidos_activos,
                                                   historial_acciones, pedidos_entregados,
                                                   mapa_ciudad);
                        test_manejo_errores(zonas, domiciliarios, restaurantes,
                                           clientes, pedidos_activos,
                                           historial_acciones, pedidos_entregados,
                                           mapa_ciudad);
                        test_estructuras_y_concurrencia(zonas, domiciliarios, restaurantes,
                                                       clientes, pedidos_activos,
                                                       historial_acciones, pedidos_entregados,
                                                       mapa_ciudad);
                        cout << "Todos los Test completados" << endl;
                        break;
                    case 0:
                        cout << "[INFO] Volviendo al menu principal..." << endl;
                        break;
                    default:
                        cout << "[ERROR] Opcion invalida" << endl;
                }
                break;
            }
            case 12:
                //Esto no se puede ver en el mapa, deberia dejarlo como un metodo de debug
                //Pero aja, ver no hace daño
                mostrarMapaCiudad(mapa_ciudad);
                break;
            case 0:
                cout << "\n[SISTEMA] Cerrando sistema..." << endl;
                cout << "Gracias por usar el sistema de pedidos!" << endl;
                break;
            default:
                cout << "\n[ERROR] Opcion invalida. Intenta de nuevo." << endl;
        }
        if (opcion != 0) {
            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while(opcion != 0);

    //Limpieza de Memoria
    delete zonas;
    delete domiciliarios;
    delete restaurantes;
    delete clientes;
    delete pedidos_activos;
    delete historial_acciones;
    delete pedidos_entregados;

    return 0;
}