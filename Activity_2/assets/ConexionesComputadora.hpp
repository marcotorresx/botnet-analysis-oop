#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "Entry.hpp"

using namespace std;

class ConexionesComputadora
{
private:
    // Crear direccion IP de equipo
    void get_ip();

    // Buscar y guardar nombre que corresponda a la IP del equipo
    void get_nombre();

public:
    // Direccion IP y nombre de equipo
    string ip, nombre;

    // Pila de conexiones entrantes
    stack<Entry> ConexionesEntrantes;

    // Fila de conexiones salientes
    queue<Entry> ConexionesSalientes;

    // Vector de entradas
    vector<Entry> entries;

    // Constructor
    ConexionesComputadora(vector<Entry>);

    //Llena la cola con los datos
    void cargar_ConexionesEntrantes();

    //llena la pila con los datos
    void cargar_ConexionesSalientes();

    // Imptimir conexiones entrantes
    void imprimir_ConexionesEntrantes();

    // Imptimir conexiones salientes
    void imprimir_ConexionesSalientes();

    // Ultima conexion entrante
    void ultimaConexionEntrante();

    // Longitud de conexiones entrantes
    void longitudEntrantes();

    // Longitud de conexiones salientes
    void longitudSalientes();

    // Revisar conexiones seguidas
    void conexionesSeguidas();
};

#endif