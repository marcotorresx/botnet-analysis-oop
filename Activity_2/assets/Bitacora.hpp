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
protected:
    // Vectores que almacena todas las entradas del archivo csv
    vector<Entry> entries;
    // Nombre del archivo csv
    string file_name;

public:
    // Total de entradas o filas del archivo
    int total_entries = 0;
    bool originNamesOrdered = false;

    // Constructor
    Bitacora(string);

    // Metodos
    void print();
    void countRegistersInADay(int);
    void searchByName(string[], int);
    void searchByMail();
    void findAllMails();
    vector<Entry> getEntries();

private:
    // Carga de los datos del csv a los vectores
    void LoadData();
};

#endif