#ifndef Bitacora_hpp
#define Bitacora_hpp

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Entry.hpp"
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

private:
    void LoadData(); // Carga de los datos del csv a los vectores
};

#endif