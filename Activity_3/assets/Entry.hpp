#ifndef Entry_hpp
#define Entry_hpp
#include <iostream>
using namespace std;

class Entry
{
public:
    // Atributos de objeto, uno por cada columna
    string fecha, hora, ip_origen, puerto_origen, nombre_origen, ip_destino, puerto_destino, nombre_destino;

    // Constructor de Entry
    Entry(string _fecha, string _hora, string ip_o, string puerto_o, string nombre_o, string ip_d, string puerto_d, string nombre_d)
    {
        fecha = _fecha;
        hora = _hora;
        ip_origen = ip_o;
        puerto_origen = puerto_o;
        nombre_origen = nombre_o;
        ip_destino = ip_d;
        puerto_destino = puerto_d;
        nombre_destino = nombre_d;
    }
};

#endif
