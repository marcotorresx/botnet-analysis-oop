#include "assets/Bitacora.cpp"
#include "assets/ConexionesComputadora.hpp"
#include <iostream>

using namespace std;

int main()
{
    // Se crea objeto de clase Bitacora que contiene los datos del CSV y las estructuras de datos
    cout << endl;
    cout << "--- Creacion de Estructuras ---" << endl;
    Bitacora e("equipo1.csv");

    // Pregunta 1
    cout << endl;
    cout << "1. Hay algun nombre de dominio en el conjunto que sea anomalo (Esto puede ser con inspeccion visual)." << endl;

    // Imprimir dominios externos
    cout << endl;
    cout << "Dominios Externos:" << endl;
    set<string>::iterator itrDE;
    for (itrDE = e.dominiosExternos.begin(); itrDE != e.dominiosExternos.end(); itrDE++)
    {
        cout << "-" << *itrDE << endl;
    }

    cout << endl;
    cout << "Dominios anomalos: 27o7wwa6btayxreesf1h.org  9o7i94oyprais2lpcztv.com" << endl;

    // Pregunta 2
    cout << endl;
    cout << endl;
    cout << "2. De los nombres de dominio encontrados en el paso anterior, cual es su IP?" << endl;

    // Se busca en el mapa dominioAIP la ip de los dominios en tiempo constante
    cout << endl;
    cout << "Se buscan las ips en tiempo constante usando un mapa que relaciona dominio - ip" << endl;
    cout << "IP de 27o7wwa6btayxreesf1h.org:  " << e.dominiosAIps["27o7wwa6btayxreesf1h.org"] << endl;
    cout << "IP de 9o7i94oyprais2lpcztv.com:  " << e.dominiosAIps["9o7i94oyprais2lpcztv.com"] << endl;

    // Pregunta 3
    cout << endl;
    cout << endl;
    cout << "3. Cantidad de ips de dominio reto.com que tienen al menos una conexion entrante." << endl;

    // Ejecutar método apropiado
    cout << endl;
    cout << "Cantidad: " << e.ipsInternasConEntrantes() << endl;

    // Pregunta 4
    cout << endl;
    cout << endl;
    cout << "4. Obten las IPs unicas de las conexiones entrantes de algunas computadoras que no sean server.reto.com o el servidor DHCP." << endl;

    // Ejecutar método apropiado
    e.obtenerIpsConexionesEntrantes();

    // Pregunta 6
    cout << endl;
    cout << endl;
    cout << "6. Para las IPs encontradas en el paso anterior, determina si se han comunicado con los datos encontrados en la pregunta 1." << endl;

    // Ejecutar método apropiado
    e.comunicacionConDominioExtano();

    // Pregunta 7
    cout << endl;
    cout << endl;
    cout << "7. Determina en que fecha ocurre la primera comunicacion entre estas dos computadoras y que protocolo se usa." << endl;

    // Ejecutar método apropiado
    e.datosDeComunicacion();

    return 0;
}
