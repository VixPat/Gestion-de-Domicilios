#include "Test.h"

void test_manejo_errores(ListaDoble<Zona*>* zonas,
                         ListaDoble<Domiciliario*>* domiciliarios,
                         ArbolBB<Restaurante*>* restaurantes,
                         ListaDoble<Cliente*>* clientes,
                         Cola<Pedido*>* pedidos_activos,
                         Pila<string>* historial_acciones,
                         ListaDoble<Pedido*>* pedidos_entregados,
                         Grafo* mapa) {
    cout << "TEST 2: Manejo de errores" << endl;
    cout << "\nCASO 1: Buscar cliente inexistente" << endl;
    Cliente* c_inexistente = buscarCliente(clientes, "C999");
    if (c_inexistente == nullptr) {
        cout << "[OK] Error detectado correctamente: Cliente C999 no existe" << endl;
    } else {
        cout << "[FAIL] Error no detectado" << endl;
    }
    cout << "\nCASO 2: Buscar restaurante inexistente" << endl;
    Restaurante* r_inexistente = buscarRestaurante(restaurantes, "R999");
    if (r_inexistente == nullptr) {
        cout << "[OK] Error detectado correctamente: Restaurante R999 no existe" << endl;
    } else {
        cout << "[FAIL] Error no detectado" << endl;
    }
    cout << "\nCASO 3: Procesar pedido con cola vacia" << endl;
    if (pedidos_activos->getSize() == 0) {
        cout << "[TEST] Cola vacia detectada correctamente" << endl;
        cout << "[OK] Sistema debe mostrar mensaje: 'No hay pedidos para procesar'" << endl;
    } else {
        cout << "[INFO] Hay " << pedidos_activos->getSize() << " pedidos en cola" << endl;
    }
    cout << "\nCASO 4: Todos los domiciliarios ocupados" << endl;
    // Ocupar todos los domiciliarios
    NodoListaDoble<Domiciliario*>* temp = domiciliarios->getHead();
    int contador_ocupados = 0;
    while (temp != nullptr) {
        temp->dato->ocupar();
        contador_ocupados++;
        temp = temp->next;
    }
    cout << "[TEST] " << contador_ocupados << " domiciliarios ocupados" << endl;
    // Intentar buscar domiciliario disponible
    Domiciliario* domi = buscarDomiciliarioDisponible(domiciliarios, mapa, "Z003");
    if (domi == nullptr) {
        cout << "[OK] Error detectado correctamente: No hay domiciliarios disponibles" << endl;
    } else {
        cout << "[FAIL] Se asigno un domiciliario ocupado" << endl;
    }
    // Liberar todos
    temp = domiciliarios->getHead();
    while (temp != nullptr) {
        temp->dato->liberar();
        temp = temp->next;
    }
    cout << "[TEST] Domiciliarios liberados para siguientes tests" << endl;
    cout << "\nCASO 5: Cancelar sin pedidos en historial" << endl;
    // Vaciar historial
    while (historial_acciones->getSize() > 0) {
        historial_acciones->pop();
    }
    if (historial_acciones->getSize() == 0) {
        cout << "[OK] Historial vacio detectado correctamente" << endl;
        cout << "[TEST] Sistema debe mostrar: 'No hay acciones para cancelar'" << endl;
    }
    cout << "\nCASO 6: Entregar pedido sin estado EN_CAMINO" << endl;
    Pedido* p_pendiente = new Pedido("PT100", "C001", "Z001");
    p_pendiente->asignarRestaurante("R001");
    p_pendiente->agregarItem("Pizza");
    // Estado: PENDIENTE (no se procesó)
    pedidos_activos->enqueue(p_pendiente);
    cout << "[TEST] Pedido PT100 en estado: " << p_pendiente->getEstado() << endl;
    // Intentar entregar (debe fallar)
    NodoColas<Pedido*>* nodo = pedidos_activos->getNodoHead();
    bool encontrado_en_camino = false;
    while (nodo != nullptr) {
        if (nodo->dato->getEstado() == "EN_CAMINO") {
            encontrado_en_camino = true;
            break;
        }
        nodo = nodo->next;
    }
    if (!encontrado_en_camino) {
        cout << "[OK] Error detectado: No hay pedidos listos para entregar" << endl;
    }
    // Limpiar
    pedidos_activos->dequeue();
    cout << "\nCASO 7: Validar plato no existe en menu" << endl;
    Restaurante* bella_italia = buscarRestaurante(restaurantes, "R001");
    if (bella_italia) {
        bool tiene_sushi = bella_italia->tienePlato("Sushi");
        if (!tiene_sushi) {
            cout << "[OK] Validacion correcta: Bella Italia no tiene Sushi" << endl;
        } else {
            cout << "[FAIL] Validacion incorrecta" << endl;
        }
        bool tiene_pizza = bella_italia->tienePlato("Pizza Margarita");
        if (tiene_pizza) {
            cout << "[OK] Validacion correcta: Bella Italia SI tiene Pizza Margarita" << endl;
        } else {
            cout << "[FAIL] Validacion incorrecta" << endl;
        }
    }
    cout << "TEST 2 COMPLETADO" << endl;
}