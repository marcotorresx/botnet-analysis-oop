#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include "Entry.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class ConexionesComputadora
{
public:
    vector<Entry> conexionesEntrantes; // Vector de conexiones entrantes
    vector<Entry> conexionesSalientes; // Vector de conexiones salientes
};

#endif