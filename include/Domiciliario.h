#ifndef DOMICILIARIO_H
#define DOMICILIARIO_H

#include <iostream>
#include <string>
using namespace std;

//Archivo include de la clase; Se detalla y comenta mas en el .cpp
//Ver el archivo .cpp para saber el uso de cada metodo
//Todo: copiar y pegar en cada clase .h

class Domiciliario {
private:
    string codigo;
    string nombre;
    string zona_actual_id;
    bool disponible;
    int pedidos_entregados;
    string vehiculo;
    float factor_velocidad;

public:
    Domiciliario(string codigo, string nombre, string zona_actual_id, string vehiculo);
    ~Domiciliario();

    string getCodigo();
    string getNombre();
    string getZonaActual();
    bool isDisponible();
    string getVehiculo();
    float getFactorVelocidad();
    int getPedidosEntregados();

    void ocupar();
    void liberar();
    void moverAZona(string zona_id);
    void incrementarEntregas();

    float calcularTiempoLlegada(float distancia);
    void mostrarInfo();

private:
    void establecerFactorVelocidad();
};

#endif //DOMICILIARIO_H