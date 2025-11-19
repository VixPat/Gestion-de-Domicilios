#include "../../include/Helpers/Helpers.h"

using namespace std;
//Metodos Auxiliares (Helpers)
//Esto es a mi parecer lo mas importante, aca voy a comentar bastante
//Estos de aca son metodos de busqueda

//Funciones de Busqueda
//Recorre el ABB hasta encontrar y retornar el puntero a Restaurante
Restaurante* buscarEnArbolRec(NodoABB<Restaurante*>* nodo, string codigo) {
    if (nodo == nullptr) return nullptr;
    if (nodo->dato->getCodigo() == codigo) {
        return nodo->dato;
    }
    Restaurante* izq = buscarEnArbolRec(nodo->left, codigo);
    if (izq != nullptr) return izq;
    return buscarEnArbolRec(nodo->right, codigo);
}
//Lo mismo pero en la lista de clientes, en este caso es una Lista Doble
Cliente* buscarCliente(ListaDoble<Cliente*>* clientes, string codigo) {
    NodoListaDoble<Cliente*>* temp = clientes->getHead();
    while (temp != nullptr) {
        if (temp->dato->getCodigo() == codigo) {
            return temp->dato;
        }
        temp = temp->next;
    }
    return nullptr;
}
//Recorre la Lista Doble de Domiciliarios
Domiciliario* buscarDomiciliario(ListaDoble<Domiciliario*>* domiciliarios, string codigo) {
    NodoListaDoble<Domiciliario*>* temp = domiciliarios->getHead();
    while (temp != nullptr) {
        if (temp->dato->getCodigo() == codigo) {
            return temp->dato;
        }
        temp = temp->next;
    }
    return nullptr;
}
//Este llama a la funcion de antes (buscarEnArbolRec) y le pasa la informacion que el necesita para hacer el recorrido
Restaurante* buscarRestaurante(ArbolBB<Restaurante*>* restaurantes, string codigo) {
    return buscarEnArbolRec(restaurantes->getRoot(), codigo);
}
//Pues aja, recorre la lista de Zona
Zona* buscarZona(ListaDoble<Zona*>* zonas, string id) {
    NodoListaDoble<Zona*>* temp = zonas->getHead();
    while (temp != nullptr) {
        if (temp->dato->getId() == id) {
            return temp->dato;
        }
        temp = temp->next;
    }
    return nullptr;
}
//Lo mismo pero en pedidos
Pedido* buscarPedido(Cola<Pedido*>* pedidos, string id) {
    if (pedidos->getSize() == 0) return nullptr;
    NodoColas<Pedido*>* temp = pedidos->getNodoHead();
    while (temp != nullptr) {
        if (temp->dato->getId() == id) {
            return temp->dato;
        }
        temp = temp->next;
    }
    return nullptr;
}

//Funciones de Distancias (Ahora si se trabaja con el Grafo)
//Metodo que se encarga de buscar Domis disponibles en base al tiempo que se demora y la zona que se encuentra
Domiciliario* buscarDomiciliarioDisponible(ListaDoble<Domiciliario*>* domiciliarios,
                                            Grafo* mapa,
                                            string zona_restaurante) {
    cout << "\n[SISTEMA] Buscando domiciliario disponible..." << endl;
    Domiciliario* mejorDomiciliario = nullptr;
    float menorTiempo = 999; //Limite de tiempo
    NodoListaDoble<Domiciliario*>* temp = domiciliarios->getHead();
    while (temp != nullptr) {
        Domiciliario* domi = temp->dato;
        //Si esta disponible calcula cuanto se demora llegando en base a la zona q se encuentra
        if (domi->isDisponible()) {
            int distancia = calcularDistancia(mapa, domi->getZonaActual(), zona_restaurante);
            float tiempo;
            if (distancia == 999) {
                tiempo = 120; //Implica q no hay ruta, antes aparecia cuando el domi no era vecino directo
            } else {
                tiempo = domi->calcularTiempoLlegada(distancia);
            }
            cout << "  - " << domi->getNombre() << " (" << domi->getVehiculo()
                 << "): " << tiempo << " min (Distancia: " << distancia << " km)" << endl;
            //El nos muestra todos, y al final escoje el mejor el base al menor tiempo
            if (tiempo < menorTiempo) {
                menorTiempo = tiempo;
                mejorDomiciliario = domi;
            }
        }
        temp = temp->next;
    }
    //Si se logro conseguir un Domi (puede q todos esten ocupados) nos lo asigna y nos muestra el tiempo estimado
    if (mejorDomiciliario != nullptr) {
        cout << "\n[ASIGNADO] " << mejorDomiciliario->getNombre()
             << " (Tiempo estimado: " << menorTiempo << " min)" << endl;
    } else {
        cout << "\n[ERROR] No hay domiciliarios disponibles." << endl;
    }
    return mejorDomiciliario;
}
//Mas abajo se puede ver el metodo que se usaba antes
//Efectivamente me parece mas ordenado asi
float calcularDistancia(Grafo* mapa, string zona1_id, string zona2_id) {
    if (zona1_id == zona2_id) return 0.0f;
    // Usar Dijkstra del grafo
    return mapa->obtenerDistancia(zona1_id, zona2_id);
}
/*Metodo para calcular la distancia entre dos zonas
 TODO Al igual que en la clase de Zona, dejo esto aca a modo de documentacion (???)
int calcularDistancia(ListaDoble<Zona*>* zonas, string zona1_id, string zona2_id) {
    //Si son la misma zona (Esto ocurre cuando queremos saber en donde se encuntra un domi, puede q este en la misma zona donde lo necesitamos)
    if (zona1_id == zona2_id) return 0;
    Zona* zona1 = buscarZona(zonas, zona1_id);
    //Llamemos a un metodo establecido en la clase de Zona pa ver cuanta distancia hay entre 2 zonas
    if (zona1 != nullptr) {
        if (zona1->esVecino(zona2_id)) {
            return zona1->getDistanciaAVecino(zona2_id);
        }
    }
    //Si no es vecino se regresa una distancia limite
    return 999;
}*/

//Metodo para crear un nuevo pedido en base al cliente, restaurante y zona
void crearPedido(ListaDoble<Cliente*>* clientes,
                 ArbolBB<Restaurante*>* restaurantes,
                 Cola<Pedido*>* pedidos_activos,
                 Pila<string>* historial_acciones) {
    cout << "\n_ Crear nuevo Pedido _" << endl;
    cout << "(Escribe 'salir' en cualquier momento para cancelar)" << endl;
    string codigo_cliente, codigo_restaurante, zona_destino;
    cout << "Codigo del cliente: ";
    cin >> codigo_cliente;
    //Verifica q el cliente exista
    Cliente* cliente = buscarCliente(clientes, codigo_cliente);
    while (cliente == nullptr) {
        cout << "\nCodigo del cliente: ";
        cin >> codigo_cliente;
        if (codigo_cliente == "salir") {
            cout << "[INFO] Operacion cancelada." << endl;
            return;
        }
        cliente = buscarCliente(clientes, codigo_cliente);
        if (cliente == nullptr) {
            cout << "[ERROR] Cliente no encontrado. Intenta de nuevo." << endl;
        }
    }
    //Verifica que la zona exista
    cout << "Zona de entrega: ";
    cin >> zona_destino;
    cout << "Codigo del restaurante: ";
    cin >> codigo_restaurante;
    Restaurante* restaurante = buscarRestaurante(restaurantes, codigo_restaurante);
    if (zona_destino == "salir") {
        cout << "[INFO] Operacion cancelada." << endl;
        return;
    }
    while (restaurante == nullptr) {
        cout << "\nCodigo del restaurante: ";
        cin >> codigo_restaurante;
        if (codigo_restaurante == "salir") {
            cout << "[INFO] Operacion cancelada." << endl;
            return;
        }
        restaurante = buscarRestaurante(restaurantes, codigo_restaurante);
        if (restaurante == nullptr) {
            cout << "[ERROR] Restaurante no encontrado. Intenta de nuevo." << endl;
        }
    }
    //Si el restaurante existe nos muestra el menu para hacer el pedido mas facilmente
    //Tmb tiene condicionales para que no ocurran error, no acepta numeros, el nombre debe ser igual
    cout << "\n_ Menu de " << restaurante->getNombre() << " _" << endl;
    restaurante->mostrarMenu();
    static int contador_pedidos = 1;
    string id_pedido = "P" + to_string(contador_pedidos++);
    Pedido* nuevoPedido = new Pedido(id_pedido, codigo_cliente, zona_destino);
    nuevoPedido->asignarRestaurante(codigo_restaurante);
    cout << "\nAgregar items al pedido (escribe 'fin' para terminar):" << endl;
    cout << "NOTA: Solo puedes pedir items que esten en el menu." << endl;
    string item;
    cin.ignore();
    int contador_items = 0;
    while (true) {
        cout << "Item: ";
        getline(cin, item);
        if (item == "salir") {
            cout << "[INFO] Pedido cancelado. Datos eliminados." << endl;
            delete nuevoPedido;//Si se cancela el pedido se elimina, limpieza de memoria
            return;
        }
        if (item == "fin") {//caso q no se agrege nada (se intente hacer un pedido vacio)
            if (contador_items == 0) {
                cout << "[ERROR] Debes agregar al menos 1 item." << endl;
                cout << "Escribe 'salir' para cancelar o continua agregando items." << endl;
                continue;
            }
            break;
        }
        if (item.empty()) {//Lo mismo
            cout << "[ERROR] El item no puede estar vacio." << endl;
            continue;
        }
        //Pequeña variable que verifica si es numero o caracter
        bool es_numero = true;
        for (char c : item) {
            if (!isdigit(c)) {
                es_numero = false;
                break;
            }
        }
        if (es_numero) {//Si es numero se elimina
            cout << "[ERROR] El item no puede ser solo numeros." << endl;
            continue;
        }
        if (!restaurante->tienePlato(item)) {//Verifica que el plato se encuentre en el menu de ese restaurante
            cout << "[ERROR] El restaurante no tiene ese plato en el menu." << endl;
            continue;
        }
        nuevoPedido->agregarItem(item);
        contador_items++;
        cout << "[OK] Item agregado (" << contador_items << " items totales)" << endl;
    }
    //Si tudo esta correcto se procesa el pedido y se actualiza la info
    pedidos_activos->enqueue(nuevoPedido);
    historial_acciones->push(id_pedido);
    cout << "\n[EXITO] Pedido " << id_pedido << " creado con " << contador_items << " items!" << endl;
}
//Metodo para procesa el pedido (Entregarlo al domi)
void procesarSiguientePedido(Cola<Pedido*>* pedidos_activos,
                              ListaDoble<Domiciliario*>* domiciliarios,
                              Grafo* mapa,
                              ArbolBB<Restaurante*>* restaurantes) {
    //Si no hay pedidos no pasa nada
    if (pedidos_activos->getSize() == 0) {
        cout << "\n[INFO] No hay pedidos para procesar." << endl;
        return;
    }
    //Si hay un o mas pedidos se actualiza sus estados a Pendiente
    cout << "\n_ Procesando siguiente Pedido _" << endl;
    NodoColas<Pedido*>* temp = pedidos_activos->getNodoHead();
    Pedido* pedido = nullptr;
    while (temp != nullptr) {
        if (temp->dato->getEstado() == "PENDIENTE") {
            pedido = temp->dato;
            break;
        }
        temp = temp->next;
    }//Si no hay pendientes pero hay pedidos entonces ya estan asignados a un Domi
    if (pedido == nullptr) {
        cout << "[INFO] No hay pedidos pendientes. Todos ya estan asignados." << endl;
        return;
    }
    //Hace la respectiva actualizacion de informacion en cada modulo y verifica que sea exitoso
    pedido->mostrarInfo();
    Restaurante* restaurante = buscarRestaurante(restaurantes, pedido->getRestauranteCodigo());
    if (restaurante == nullptr) {
        cout << "[ERROR] Restaurante no encontrado." << endl;
        return;
    }
    cout << "\n[SISTEMA] Buscando domiciliario disponible..." << endl;
    Domiciliario* domiciliario = buscarDomiciliarioDisponible(domiciliarios, mapa, restaurante->getZonaId());
    if (domiciliario == nullptr) {
        cout << "[ERROR] No hay domiciliarios disponibles." << endl;
        return;
    }
    //Si no hay errores y se encuentra un Domi cercano disponible (o no tan cercano pero disponible)
    //se continua con el pedido y se actualiza su estado
    pedido->asignarDomiciliario(domiciliario->getCodigo());
    domiciliario->ocupar();
    pedido->cambiarEstado("EN_CAMINO");
    cout << "\n[INFO] Estado del pedido: PENDIENTE -> EN_CAMINO" << endl;
    cout << "[EXITO] Pedido asignado a " << domiciliario->getNombre() << "!" << endl;
}
//Metodo que entrega el pedido al cliente (si no se cancelo antes) y actualiza el estado del Domi
void entregarPedido(Cola<Pedido*>* pedidos_activos,
                    ListaDoble<Pedido*>* pedidos_entregados,
                    ListaDoble<Domiciliario*>* domiciliarios,
                    ListaDoble<Cliente*>* clientes) {
    //Verificaciones rudimentarias pa evitar errores, si hay mas de esto pondre verificaciones o ya
    if (pedidos_activos->getSize() == 0) {
        cout << "\n[INFO] No hay pedidos activos." << endl;
        return;
    }
    cout << "\n_ Entregar Pedido _" << endl;
    NodoColas<Pedido*>* temp = pedidos_activos->getNodoHead();
    Pedido* pedido = nullptr;
    while (temp != nullptr) {
        if (temp->dato->getEstado() == "EN_CAMINO") {
            pedido = temp->dato;
            break;
        }
        temp = temp->next;
    }
    if (pedido == nullptr) {
        cout << "[INFO] No hay pedidos listos para entregar." << endl;
        cout << "Los pedidos deben estar en estado EN_CAMINO." << endl;
        return; //Solo se pueden entregar pedido que esten en camino, no pendientes, ni nada, solo en camino, eso es una verificacion
    }
    string codigo_domi = pedido->getDomiciliarioCodigo();
    Domiciliario* domi = buscarDomiciliario(domiciliarios, codigo_domi);
    bool eliminado = pedidos_activos->removeIf([pedido](Pedido* p) {
        return p->getId() == pedido->getId();
    });
    if (!eliminado) {
        cout << "[ERROR] No se pudo eliminar el pedido de la cola." << endl;
        return; //Verificacion de la cola
    }
    //Caso que todo vaya bien
    cout << "[SISTEMA] Procesando entrega..." << endl;
    cout << "[EXITO] Pedido " << pedido->getId() << " entregado!" << endl;
    pedido->cambiarEstado("ENTREGADO");
    //Se actualiza el domi, ya no esta ocupado y se cambia su zona actual (creo q hable de esto antes)
    if (domi != nullptr) {
        domi->liberar();
        domi->incrementarEntregas();
        cout << "[INFO] " << domi->getNombre() << " ahora esta disponible." << endl;
    }
    //Se agrega al historial del cliente
    pedidos_entregados->insertTail(pedido);
    string codigo_cliente = pedido->getClienteCodigo();
    Cliente* cliente = buscarCliente(clientes, codigo_cliente);
    if (cliente != nullptr) {
        cliente->agregarAlHistorial(pedido->getId());
    }
}
//Metodo que cancela el ultimo pedido registrado
//TODO: No lo arreglare pero quiero q sepan q se cancela SIEMPRE el ultimo pedido
//Eso pasa pq se usa una Pila, y solo se puede cancelar ese, si queremos cancelar un pedido anterior a ese (aunq no se haya entregado) no se puede
void cancelarUltimoPedido(Pila<string>* historial_acciones,
                          Cola<Pedido*>* pedidos_activos,
                          ListaDoble<Domiciliario*>* domiciliarios) {
    //Verificaciones
    if (pedidos_activos->getSize() == 0) {
        cout << "\n[INFO] No hay pedidos activos para cancelar." << endl;
        return;
    }
    if (historial_acciones->getSize() == 0) {
        cout << "\n[INFO] No hay acciones para cancelar." << endl;
        return;
    }
    cout << "\n_ Cancelar ultimo Pedido _" << endl;
    string ultimo_pedido_id = historial_acciones->pop();
    cout << "[SISTEMA] Cancelando pedido " << ultimo_pedido_id << "..." << endl;
    Pedido* pedido = buscarPedido(pedidos_activos, ultimo_pedido_id);
    if (pedido == nullptr) {
        cout << "[ERROR] Pedido no encontrado en la cola." << endl;
        cout << "[INFO] Es posible que ya haya sido entregado." << endl;
        return;
    }
    string estado_actual = pedido->getEstado();
    string codigo_domi = pedido->getDomiciliarioCodigo();
    //Un aviso de que estabe en camino
    if (!codigo_domi.empty()) {
        Domiciliario* domi = buscarDomiciliario(domiciliarios, codigo_domi);
        if (domi != nullptr) {
            domi->liberar();
            if (estado_actual == "EN_CAMINO") {
                cout << "[ALERTA] El pedido estaba EN_CAMINO!" << endl;
                cout << "[INFO] " << domi->getNombre() << " va a regresar al punto de partida." << endl;
            }
            //Actualiza estado del Domi
            cout << "[INFO] Domiciliario " << domi->getNombre() << " liberado." << endl;
        }
    }
    //Se elimina y nos avisa si se pudo o no
    bool eliminado = pedidos_activos->removeIf([ultimo_pedido_id](Pedido* p) {
        return p->getId() == ultimo_pedido_id;
    });
    if (eliminado) {
        cout << "[EXITO] Pedido " << ultimo_pedido_id << " cancelado y eliminado!" << endl;
    } else {
        cout << "[ERROR] No se pudo eliminar el pedido de la cola." << endl;
    }
}
//"Getters" mas completos de las estructuras globales, no de un atributo en especifico
void mostrarRestaurantes(ArbolBB<Restaurante*>* restaurantes) {
    cout << "\n_ Restaurantes disponibles _" << endl;
    cout << "[INFO] Recorrido del arbol (in-order):" << endl;
    restaurantes->inOrden();
}
void mostrarRestauranteConMenu(ArbolBB<Restaurante*>* restaurantes, string codigo) {
    cout << "\n_ Menu del Restaurante _" << endl;
    Restaurante* restaurante = buscarRestaurante(restaurantes, codigo);
    if (restaurante == nullptr) {
        cout << "[ERROR] Restaurante no encontrado." << endl;
        return;
    }
    restaurante->mostrarInfo();
    restaurante->mostrarMenu();
}
void mostrarPedidosActivos(Cola<Pedido*>* pedidos_activos) {
    cout << "\n_ Pedidos activos _" << endl;
    if (pedidos_activos->getSize() == 0) {
        cout << "No hay pedidos activos." << endl;
        return;
    }
    cout << "Total de pedidos: " << pedidos_activos->getSize() << endl;
    NodoColas<Pedido*>* temp = pedidos_activos->getNodoHead();
    int contador = 1;
    while (temp != nullptr) {
        cout << "\n_ Pedido #" << contador << "_" << endl;
        temp->dato->mostrarInfo();
        temp = temp->next;
        contador++;
    }
}
void mostrarDomiciliarios(ListaDoble<Domiciliario*>* domiciliarios) {
    cout << "\n_ Domiciliarios _" << endl;
    if (domiciliarios->getSize() == 0) {
        cout << "No hay domiciliarios registrados." << endl;
        return;
    }
    NodoListaDoble<Domiciliario*>* temp = domiciliarios->getHead();
    int contador = 1;
    while (temp != nullptr) {
        cout << "\n_ Domiciliario #" << contador << "_" << endl;
        temp->dato->mostrarInfo();
        temp = temp->next;
        contador++;
    }
}
void recorrerListaClientes(ListaDoble<Cliente*>* clientes) {
    cout << "\n_ Lista de Clientes _" << endl;
    if (clientes->getSize() == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }
    NodoListaDoble<Cliente*>* temp = clientes->getHead();
    int contador = 1;
    while (temp != nullptr) {
        cout << "\n_ Cliente #" << contador << " _" << endl;
        temp->dato->mostrarInfo();
        temp = temp->next;
        contador++;
    }
}
//Este pide el id del cliente y busca su historial, es mas especifico pero funciona igual q los otros getters
void verHistorialCliente(ListaDoble<Cliente*>* clientes) {
    cout << "\n_ Historial de Cliente _" << endl;
    string codigo;
    cout << "Codigo del cliente: ";
    cin >> codigo;
    Cliente* cliente = buscarCliente(clientes, codigo);
    if (cliente == nullptr) {
        cout << "[ERROR] Cliente no encontrado." << endl;
        return;
    }
    cliente->mostrarInfo();
    cliente->verHistorial();
}


// Funcion de visualizacion en base al Grafo (mas q nada pa ver si funciona)
void mostrarMapaCiudad(Grafo* mapa) {
    cout << "Mapa de la Ciudad" << endl;
    cout << "\nZonas: Norte(Z001), Sur(Z002), Centro(Z003), Este(Z004), Oeste(Z005)" << endl;
    cout << "\nDistancias desde cada zona:" << endl;

    mapa->mostrarDistanciasDijkstra("Z001");
    mapa->mostrarDistanciasDijkstra("Z002");
    mapa->mostrarDistanciasDijkstra("Z003");
    mapa->mostrarDistanciasDijkstra("Z004");
    mapa->mostrarDistanciasDijkstra("Z005");
}