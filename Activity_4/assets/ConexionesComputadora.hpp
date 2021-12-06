#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include "Entry.hpp"
#include "TreeNode.hpp"
#include "Graph.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class ConexionesComputadora
{
private:
    void get_ip();     // Crear direccion IP de equipo
    void get_nombre(); // Buscar y guardar nombre que corresponda a la IP del equipo

public:
    string ip_interna, ip_extrana, ip_alta;               // Direccion IP y nombre de equipo
    string nombre_interna, nombre_alta;                   // Direccion IP y nombre de equipo
    vector<Entry> entries;                                // Vector de entradas
    stack<Entry> ConexionesEntrantes;                     // Pila de conexiones entrantes
    queue<Entry> ConexionesSalientes;                     // Fila de conexiones salientes
    map<string, Graph<string, int>> MapaGrafosRedInterna; // Grafo con conexiones de red interna
    map<string, Graph<string, int>> MapaGrafosSitiosWeb;  // Grafo con conexiones a sitios web

    ConexionesComputadora(vector<Entry> &); // Constructor
    void cargar_Datos();                    // Llena las estructuras con los datos
    void imprimir_ConexionesEntrantes();    // Imprimir conexiones entrantes
    void imprimir_ConexionesSalientes();    // Imptimir conexiones salientes
    void ultimaConexionEntrante();          // Ultima conexion entrante
    void longitudEntrantes();               // Longitud de conexiones entrantes
    void longitudSalientes();               // Longitud de conexiones salientes
    void conexionesSeguidas();              // Revisar conexiones seguidas

    map<string, int> conexionesPorDia(string);                // Ver cantidad de conexiones en un día
    vector<TreeNode<int> *> topConexionesPorDia(int, string); // Top N de conexiones por día
    void top5TodosLosDias();                                  // Sitios en el top 5 todos los días
    void top5APartirDeUnDia();                                // Sitios en el top a partir de un día
    string conexionMasAltaNormal();                           // conexiones más altas de lo normal

    void cargarGrafos();                     // Se cargan los grafos por cada día
    void ConexionesDeAPorDia(bool);          // Determina la cantidad de conexiones de A por día
    void VerticeConMasConexionesSalientes(); // Determinar si A es el vértice con más conexiones salientes
    void ConexionesSitoB();                  // Determina la cantidad de conexiones entrantes a B por día
    void ConexionesSitoC();                  // Determina la cantidad de conexiones entrantes a C por día
};

#endif