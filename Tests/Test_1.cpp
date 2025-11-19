#include "Test.h"

void test_flujo_completo_exitoso(ListaDoble<Zona*>* zonas,
                                   ListaDoble<Domiciliario*>* domiciliarios,
                                   ArbolBB<Restaurante*>* restaurantes,
                                   ListaDoble<Cliente*>* clientes,
                                   Cola<Pedido*>* pedidos_activos,
                                   Pila<string>* historial_acciones,
                                   ListaDoble<Pedido*>* pedidos_entregados,
                                   Grafo* mapa) {
    cout << "TEST 1: Flujo ideal - Exitoso" << endl;
    cout << "\nCASO 1: Pedido simple exitoso" << endl;
    // Crear pedido manualmente
    Pedido* p1 = new Pedido("PT001", "C001", "Z001");
    p1->asignarRestaurante("R002");
    p1->agregarItem("Arroz Chino");
    p1->agregarItem("Wantan");
    pedidos_activos->enqueue(p1);
    historial_acciones->push("PT001");
    
    cout << "[TEST] Pedido PT001 creado y agregado a la cola" << endl;
    cout << "Cliente: C001 | Restaurante: R002 (Dragon Dorado - Norte)" << endl;
    cout << "Items: Arroz Chino, Wantan" << endl;
    cout << "\n[TEST] Procesando pedido..." << endl;
    Restaurante* rest = buscarRestaurante(restaurantes, "R002");
    if (rest) {
        cout << "Restaurante en zona: " << rest->getZonaId() << endl;
        Domiciliario* domi = buscarDomiciliarioDisponible(domiciliarios, mapa, rest->getZonaId());
        if (domi) {
            p1->asignarDomiciliario(domi->getCodigo());
            domi->ocupar();
            p1->cambiarEstado("EN_CAMINO");
            cout << "[OK] Domiciliario asignado exitosamente" << endl;
        }
    }
    // Entregar pedido
    cout << "\n[TEST] Entregando pedido..." << endl;
    Pedido* pedido_entregar = pedidos_activos->dequeue();
    if (pedido_entregar) {
        Domiciliario* domi = buscarDomiciliario(domiciliarios, pedido_entregar->getDomiciliarioCodigo());
        pedido_entregar->cambiarEstado("ENTREGADO");
        pedidos_entregados->insertTail(pedido_entregar);
        if (domi) {
            domi->liberar();
            domi->incrementarEntregas();
        }
        Cliente* cliente = buscarCliente(clientes, "C001");
        if (cliente) {
            cliente->agregarAlHistorial("PT001");
        }
        cout << "[OK] Pedido entregado exitosamente" << endl;
    }
    // Verificar historial
    cout << "\n[TEST] Verificando historial del cliente..." << endl;
    Cliente* c = buscarCliente(clientes, "C001");
    if (c) {
        c->verHistorial();
    }
    cout << "\nCASO 2: Multiples pedidos en orden" << endl;
    Pedido* p2 = new Pedido("PT002", "C002", "Z003");
    p2->asignarRestaurante("R001");
    p2->agregarItem("Pizza Margarita");
    pedidos_activos->enqueue(p2);
    historial_acciones->push("PT002");
    
    Pedido* p3 = new Pedido("PT003", "C003", "Z005");
    p3->asignarRestaurante("R005");
    p3->agregarItem("Hamburguesa");
    p3->agregarItem("Papas Fritas");
    pedidos_activos->enqueue(p3);
    historial_acciones->push("PT003");
    cout << "[TEST] 2 pedidos adicionales creados" << endl;
    cout << "[TEST] Total en cola: " << pedidos_activos->getSize() << endl;
    // Mostrar todos los pedidos
    cout << "\n[TEST] Mostrando pedidos activos:" << endl;
    mostrarPedidosActivos(pedidos_activos);
    cout << "\nCASO 3: Asignacion por cercania" << endl;
    cout << "[TEST] Pedido PT002 debe asignarse al domiciliario mas cercano a Z003 (Centro)" << endl;
    Restaurante* r1 = buscarRestaurante(restaurantes, "R001");
    if (r1) {
        Domiciliario* mejor = buscarDomiciliarioDisponible(domiciliarios, mapa, r1->getZonaId());
        if (mejor) {
            cout << "[OK] Se asigno: " << mejor->getNombre() << " con vehiculo " << mejor->getVehiculo() << endl;
        }
    }
    cout << "TEST 1 COMPLETADO" << endl;
}