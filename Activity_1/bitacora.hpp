#ifndef bitacora_cpp
#define bitacora_cpp

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

class Bitacora
{
protected:
    // Vectores para almacenar los datos de cada columna del csv
    vector<string> fecha, hora, ip_origen, puerto_origen, nombre_origen, ip_destino, puerto_destino, nombre_destino;

    // Nombre del archivo csv
    string file_name;

public:
    int total_entries = 0; // Total de entradas o filas del archivo

    // Constructor
    Bitacora(string);

    // Metodos
    void print();
    void countRegistersInADay(int);
    void searchByName(string[], int);
    void SearchInternalIp();
    void searchByMail();
    void findAllMails();
    void PrintPorts();

private:
    // Carga de los datos del csv a los vectores
    void LoadData();
};

#endif