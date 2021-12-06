#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include "Entry.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <map>

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

    // Ver cantidad de conexiones en un día con un mapa
    map<string, int> conexionesPorDia(string);

    // Mostrar el top N de conexiones por día
    vector<TreeNode<int> *> topConexionesPorDia(int, string);

    // Mostrar si hubo un sitio que estuviera en el top 5 todos los días
    void top5TodosLosDias();

    // Mostrar si hubo un sitio que estuviera en el top a partir de un día
    void top5APartirDeUnDia();

    void conexionMasAltaNormal();
};

#endif