#include "../include/Domiciliario.h"
//Constructor y Destructor
Domiciliario::Domiciliario(string codigo, string nombre, string zona_actual_id, string vehiculo) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->zona_actual_id = zona_actual_id;
    this->vehiculo = vehiculo;
    this->disponible = true;
    this->pedidos_entregados = 0;
    establecerFactorVelocidad();
}
Domiciliario::~Domiciliario() {
    // No hay memoria dinámica que liberar, bruh
}

//Metodos getters, no es necesario especificarlos, si tiene dudas revise Cliente.cpp
//Ahi se puede dar una idea de como funcionan los getters con solo ver los nombres
string Domiciliario::getCodigo() {
    return codigo;
}
string Domiciliario::getNombre() {
    return nombre;
}
string Domiciliario::getZonaActual() {
    return zona_actual_id;
}
bool Domiciliario::isDisponible() {
    return disponible; //Este es un boolean
}
string Domiciliario::getVehiculo() {
    return vehiculo;
}
float Domiciliario::getFactorVelocidad() {
    return factor_velocidad;
}
int Domiciliario::getPedidosEntregados() {
    return pedidos_entregados;
}

//Metodos de la clase
//Este es para ocuparlo (Q reciba un pedido y lo lleve, aunq todavia no esta entregado)
void Domiciliario::ocupar() {
    disponible = false;
    cout << nombre << " Ahora esta ocupado." << endl;
}
//Lo opuesto al anterior, se usa si el pedido se entrega o se cancela
void Domiciliario::liberar() {
    disponible = true;
    cout << nombre << " Ahora esta disponible." << endl;
}
//Lo que mencionamos en la DB, si entrega el pedido exitosamente se actualiza su zona en donde se entrego el pedido.
void Domiciliario::moverAZona(string zona_id) {
    cout << nombre << " se movio de " << zona_actual_id << " a " << zona_id << endl;
    zona_actual_id = zona_id;
}
//Si realiza una entrega exitosa se actualiza su numero total de entregas realizadas
void Domiciliario::incrementarEntregas() {
    pedidos_entregados++;
}
//En base al vehiculo (cada uno cuenta con factos de velocidad, se puede ver en un metodo q esta mas abajo (establecerFactorVelocidad))
//Se tiene un limite de tiempo, si esta muy lejos no dira que se demora 16 horas en llegar (eso ocurrio antes, por eso puse el limite)
float Domiciliario::calcularTiempoLlegada(float distancia) {
    float tiempo = distancia / factor_velocidad;
    if (tiempo > 120) {
        tiempo = 120;
    }
    return tiempo;
}
//Metodo para ver la info completa del Domi
void Domiciliario::mostrarInfo() {
    cout << "\n_ Informacion del Domiciliario _" << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Zona actual: " << zona_actual_id << endl;
    cout << "Vehiculo: " << vehiculo << endl;
    cout << "Estado: " << (disponible ? "Disponible" : "Ocupado") << endl;
    cout << "Pedidos entregados: " << pedidos_entregados << endl;
    cout << "Factor de velocidad: " << factor_velocidad << "x" << endl;
}
//Lo que se hablo antes, el facto de velocidad, depende del vehiculo, si no se especifica el vehiculo se pone uno en automatico
//Esto no es taaan relevante pq los Domi se añaden de forma automatica (en DB) perooooo
//si mas adelante se añade la funcion pues ya esta especificado eso, o si se escribe mal el nombre
void Domiciliario::establecerFactorVelocidad() {
    if (vehiculo == "bicicleta") {
        factor_velocidad = 1.0;
    } else if (vehiculo == "moto") {
        factor_velocidad = 2.0;
    } else if (vehiculo == "carro") {
        factor_velocidad = 1.5;
    } else {
        factor_velocidad = 1.0;
        cout << "Vehiculo no reconocido. Usando velocidad por defecto." << endl;
    }
}