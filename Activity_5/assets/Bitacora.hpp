#ifndef Bitacora_hpp
#define Bitacora_hpp

#include "ConexionesComputadora.hpp"
#include "Entry.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

class Bitacora
{
public:
    string file_name;      // Nombre del archivo csv
    vector<Entry> entries; // Vectores que almacena todas las entradas del archivo csv
    int total_entries;     // Total de entradas o filas del archivo

    Bitacora(string);                 // Constructor
    void print();                     // Imprime las primeras 30 filas
    void countRegistersInADay(int);   // Contar cantidad de registros del día especificado
    void searchByName(string[], int); // Busca un nombre en especifico dentro del vector nombre de origen
    void searchByMail();              // Buscar nombre de computadora
    void findAllMails();              // Encuentra e imprime todos los servicios de mensajería usados

    set<string> dominiosExternos;                      // Set con los dominios que no pertenezcan al dominio reto.com
    map<string, string> dominiosAIps;                  // Mapa de los dominios y su ip
    map<string, string> ipsADominios;                  // Mapa de las ips y su dominio
    map<string, ConexionesComputadora> ipsAConexiones; // Mapa de ips con sus conexiones
    vector<string> ipsSeleccionadas;                   // Vector que contendrá las ips seleccionadas
    set<string> ipsConexionesEntrantesSeleccionadas;   // Set de las ips de conexiones entrantes de las ips seleccionadas
    vector<string> conexionesADominioExtrano;          // Vector de ips que se han comunicado con el dominio extraño

    int ipsInternasConEntrantes();        // Calcula cantidad de ips de dominio reto.com que tienen al menos una conexion entrante
    void obtenerIpsConexionesEntrantes(); // Obtener las ips unicas de las conexiones entrantes de algunas computadoras de la red interna
    void comunicacionConDominioExtano();  // Deteminar si las ips unicas de las conexiones entrantes se han comunicado con el dominio raro
    void datosDeComunicacion();           // Mostrar datos de las primeras conexiones entre las compuadoras y el dominio extraño

private:
    void LoadData();        // Carga de los datos del csv a los vectores
    void loadEstructuras(); // Se cargan las estructuras de datos
};

#endif