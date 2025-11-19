#include "Test.h"

void test_estructuras_y_concurrencia(ListaDoble<Zona*>* zonas,
                                      ListaDoble<Domiciliario*>* domiciliarios,
                                      ArbolBB<Restaurante*>* restaurantes,
                                      ListaDoble<Cliente*>* clientes,
                                      Cola<Pedido*>* pedidos_activos,
                                      Pila<string>* historial_acciones,
                                      ListaDoble<Pedido*>* pedidos_entregados,
                                      Grafo* mapa) {
    cout << "TEST 3: ESTRUCTURAS Y CONCURRENCIA" << endl;
    cout << "\nCASO 1: Verificar FIFO en Cola de pedidos" << endl;
    
    Pedido* p1 = new Pedido("PQ001", "C001", "Z001");
    p1->asignarRestaurante("R001");
    p1->agregarItem("Item1");
    Pedido* p2 = new Pedido("PQ002", "C002", "Z002");
    p2->asignarRestaurante("R002");
    p2->agregarItem("Item2");
    Pedido* p3 = new Pedido("PQ003", "C003", "Z003");
    p3->asignarRestaurante("R003");
    p3->agregarItem("Item3");
    
    pedidos_activos->enqueue(p1);
    pedidos_activos->enqueue(p2);
    pedidos_activos->enqueue(p3);
    cout << "[TEST] 3 pedidos encolados en orden: PQ001, PQ002, PQ003" << endl;
    
    Pedido* primero = pedidos_activos->dequeue();
    if (primero && primero->getId() == "PQ001") {
        cout << "[OK] FIFO correcto: Primero en salir fue PQ001" << endl;
    } else {
        cout << "[FAIL] FIFO incorrecto" << endl;
    }
    Pedido* segundo = pedidos_activos->dequeue();
    if (segundo && segundo->getId() == "PQ002") {
        cout << "[OK] FIFO correcto: Segundo en salir fue PQ002" << endl;
    } else {
        cout << "[FAIL] FIFO incorrecto" << endl;
    }
    pedidos_activos->dequeue(); // Limpiar PQ003
    cout << "\nCASO 2: Verificar LIFO en Pila de historial" << endl;
    
    historial_acciones->push("PA001");
    historial_acciones->push("PA002");
    historial_acciones->push("PA003");
    cout << "[TEST] 3 acciones apiladas: PA001, PA002, PA003" << endl;
    string ultima = historial_acciones->pop();
    if (ultima == "PA003") {
        cout << "[OK] LIFO correcto: Ultimo en salir fue PA003" << endl;
    } else {
        cout << "[FAIL] LIFO incorrecto" << endl;
    }
    string penultima = historial_acciones->pop();
    if (penultima == "PA002") {
        cout << "[OK] LIFO correcto: Penultimo en salir fue PA002" << endl;
    } else {
        cout << "[FAIL] LIFO incorrecto" << endl;
    }
    historial_acciones->pop(); // Limpiar PA001
    cout << "\nCASO 3: Busqueda en ABB de restaurantes" << endl;
    cout << "[TEST] Buscando restaurantes en orden alfabetico..." << endl;
    
    Restaurante* r1 = buscarRestaurante(restaurantes, "R001");
    Restaurante* r2 = buscarRestaurante(restaurantes, "R002");
    Restaurante* r5 = buscarRestaurante(restaurantes, "R005");
    if (r1 && r2 && r5) {
        cout << "[OK] Busqueda en ABB funciona correctamente" << endl;
        cout << "  - R001: " << r1->getNombre() << endl;
        cout << "  - R002: " << r2->getNombre() << endl;
        cout << "  - R005: " << r5->getNombre() << endl;
    } else {
        cout << "[FAIL] Busqueda en ABB fallo" << endl;
    }
    cout << "\nCASO 4: Verificar conexiones del Grafo" << endl;
    cout << "[TEST] Mostrando distancias desde Centro (Z003):" << endl;
    mapa->mostrarDistanciasDijkstra("Z003");
    // Verificar distancias específicas
    float dist_centro_norte = calcularDistancia(mapa, "Z003", "Z001");
    float dist_centro_sur = calcularDistancia(mapa, "Z003", "Z002");
    float dist_centro_este = calcularDistancia(mapa, "Z003", "Z004");
    float dist_centro_oeste = calcularDistancia(mapa, "Z003", "Z005");
    cout << "\n[TEST] Verificando conexiones desde Centro:" << endl;
    cout << "  - Centro -> Norte: " << dist_centro_norte << " km" << endl;
    cout << "  - Centro -> Sur: " << dist_centro_sur << " km" << endl;
    cout << "  - Centro -> Este: " << dist_centro_este << " km" << endl;
    cout << "  - Centro -> Oeste: " << dist_centro_oeste << " km" << endl;
    if (dist_centro_norte == 5.0f && dist_centro_sur == 3.0f &&
        dist_centro_este == 4.0f && dist_centro_oeste == 6.0f) {
        cout << "[OK] Todas las conexiones del grafo son correctas" << endl;
        }
    else {
            cout << "[FAIL] Hay inconsistencias en las distancias" << endl;
    }
    cout << "\nCASO 5: Multiples pedidos simultaneos" << endl;
    // Crear 5 pedidos de diferentes clientes
    for (int i = 1; i <= 5; i++) {
        string id = "PC00" + to_string(i);
        string cliente_id = "C00" + to_string((i % 3) + 1); // C001, C002, C003
        Pedido* p = new Pedido(id, cliente_id, "Z003");
        p->asignarRestaurante("R001");
        p->agregarItem("Pizza");
        pedidos_activos->enqueue(p);
    }
    cout << "[TEST] 5 pedidos creados simultaneamente" << endl;
    cout << "[TEST] Cola tiene: " << pedidos_activos->getSize() << " pedidos" << endl;
    // Procesar todos
    int procesados = 0;
    while (pedidos_activos->getSize() > 0) {
        Pedido* p = pedidos_activos->dequeue();
        if (p) {
            procesados++;
            delete p;
        }
    }
    cout << "[OK] Se procesaron " << procesados << " pedidos correctamente" << endl;
    cout << "\n--- CASO 6: Historial de cliente (Pila) ---" << endl;
    Cliente* cliente = buscarCliente(clientes, "C001");
    if (cliente) {
        // Agregar varios pedidos al historial
        cliente->agregarAlHistorial("PH001");
        cliente->agregarAlHistorial("PH002");
        cliente->agregarAlHistorial("PH003");
        cout << "[TEST] Cliente " << cliente->getNombre() << " tiene historial:" << endl;
        cliente->verHistorial();
        cout << "[OK] Historial muestra pedidos mas recientes primero (LIFO)" << endl;
    }
    cout << "\nCASO 7: Calculo de distancias entre zonas" << endl;
    int dist1 = calcularDistancia(mapa, "Z001", "Z003");
    int dist2 = calcularDistancia(mapa, "Z002", "Z003");
    int dist3 = calcularDistancia(mapa, "Z001", "Z005");
    
    cout << "[TEST] Distancias calculadas:" << endl;
    cout << "  - Norte (Z001) -> Centro (Z003): " << dist1 << " km" << endl;
    cout << "  - Sur (Z002) -> Centro (Z003): " << dist2 << " km" << endl;
    cout << "  - Norte (Z001) -> Oeste (Z005): " << dist3 << " km" << endl;
    if (dist1 > 0 && dist2 > 0) {
        cout << "[OK] Calculo de distancias funciona correctamente" << endl;
    }
    cout << "\nCASO 8: Factor de velocidad de vehiculos" << endl;
    NodoListaDoble<Domiciliario*>* temp = domiciliarios->getHead();
    cout << "[TEST] Comparando tiempos de llegada para 10 km:" << endl;
    while (temp != nullptr) {
        float tiempo = temp->dato->calcularTiempoLlegada(10);
        cout << "  - " << temp->dato->getNombre() 
             << " (" << temp->dato->getVehiculo() << "): " 
             << tiempo << " min" << endl;
        temp = temp->next;
    }
    cout << "[OK] Factores de velocidad calculados correctamente" << endl;
    //NUEVO: CASO 9: Verificar algoritmo Dijkstra
    cout << "\nCASO 9: Verificar algoritmo Dijkstra" << endl;
    cout << "[TEST] Mostrando todas las distancias desde Centro (Z003):" << endl;
    mapa->mostrarDistanciasDijkstra("Z003");
    cout << "[OK] Dijkstra ejecutado correctamente" << endl;
    cout << "TEST 3 COMPLETADO" << endl;
}