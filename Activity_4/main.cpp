#include "assets/Bitacora.cpp"
#include "assets/ConexionesComputadora.cpp"
#include <iostream>

using namespace std;

int main()
{
    // Se crea objeto de clase Bitacora que contiene los datos del CSV
    Bitacora entries("equipo1.csv");

    // Se crea objeto de clase ConexionesComputadora que contiene las diferentes conexiones
    ConexionesComputadora conexiones(entries.entries);

    conexiones.cargarGrafos();

    cout << endl;
    cout << "1) Determina la cantidad de computadoras con las que se ha conectado A por dia." << endl;
    cout << endl;
    cout << "Conexiones salientes de A por dia: " << endl;
    conexiones.ConexionesDeAPorDia(false);

    cout << endl;
    cout << "2) Es el vertice que mas conexiones salientes tiene hacia la red interna?" << endl;
    cout << endl;
    conexiones.VerticeConMasConexionesSalientes();

    cout << endl;
    cout << "3) Ubica la cantidad de computadoras que se han conectado hacia A por dia. Existen conexiones de las demas computadoras hacia A?" << endl;
    cout << endl;
    cout << "Conexiones entrantes de A por dia: " << endl;
    conexiones.ConexionesDeAPorDia(true);

    cout << endl;
    cout << "4) Utilizando un grafo de conexiones a sitios web, determina cuantas computadoras se han conectado a B por dia." << endl;
    cout << endl;
    cout << "Conexiones entrantes a B por dia: " << endl;
    conexiones.ConexionesSitoB();

    cout << endl;
    cout << "5) Utilizando el mismo grafo del punto anterior, indica cuantas computadoras se han conectado a C por dia" << endl;
    cout << endl;
    cout << "Conexiones entrantes a C por dia: " << endl;
    conexiones.ConexionesSitoC();

    return 0;
}
