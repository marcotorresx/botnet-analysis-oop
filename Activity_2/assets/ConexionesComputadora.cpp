#include "ConexionesComputadora.hpp"
#include <stack>
#include <queue>

using namespace std;

// Constructor
ConexionesComputadora::ConexionesComputadora(vector<Entry> _entries)
{
    entries = _entries;
    get_ip();                     // Se crea el ip de equipo
    get_nombre();                 // Se busca y guarda el nombre de nuestra computadora
    cargar_ConexionesEntrantes(); // Se cargan conexiones entrantes
    cargar_ConexionesSalientes(); // Se cargan conexiones salientes
}

// Crear ip de equipo con numero ingresado
void ConexionesComputadora::get_ip()
{
    string number;

    // Se ingresa numero entre 1 a 150
    cout << "Ingresa el ultimo numero de tu direccion de ip (1-150): ";
    cin >> number;

    string incomplete_ip = "192.168.144";

    // Se crea ip de equipo
    ip = incomplete_ip + "." + number;
}

void ConexionesComputadora::get_nombre()
{
    // Iterar por los registros hasta encontrar nombre de la direccion de ip establecida por los usuarios y guardar el nombre de dicho registro
    for (int i = 0; i < entries.size(); i++)
    {
        // Si se encuentra la conexion con la misma ip, agregar a la cola
        if (entries[i].ip_origen == ip)
        {
            nombre = entries[i].nombre_origen;
            break; // Una vez se encuentra sal del ciclo
        }
    }
}

// Cargar conexiones entrantes
void ConexionesComputadora::cargar_ConexionesEntrantes()
{
    /*
    Las conexiones entrantes son aquellas donde la dirección IP de este 
    equipo se encuentra como dirección IP destino.
    */

    // Iterar sobre todos los registros
    for (int i = 0; i < entries.size(); i++)
    {
        // Si se encuentra la conexion con la misma ip destino, agregar a la pila
        if (entries[i].ip_destino == ip)
        {
            ConexionesEntrantes.push(entries[i]);
        }
    }
}

// Cargar conexiones salientes
void ConexionesComputadora::cargar_ConexionesSalientes()
{
    /* 
    Las conexiones salientes son aquellas donde la dirección IP de 
    este equipo se encuentra como dirección IP origen
    */

    // Iterar sobre todos los registros
    for (int i = 0; i < entries.size(); i++)
    {
        // Si se encuentra la conexion con la misma ip origen, agregar a la cola
        if (entries[i].ip_origen == ip)
        {
            ConexionesSalientes.push(entries[i]);
        }
    }
}

// Imprimir conexiones entrantes
void ConexionesComputadora::imprimir_ConexionesEntrantes()
{
    stack<Entry> CopiaConexionesEntrantes = ConexionesEntrantes;

    cout << endl;
    while (!CopiaConexionesEntrantes.empty())
    {
        // Imprime conexion top
        cout << CopiaConexionesEntrantes.top().fecha << " | "
             << CopiaConexionesEntrantes.top().hora << " | "
             << CopiaConexionesEntrantes.top().ip_origen << " | "
             << CopiaConexionesEntrantes.top().puerto_origen << " | "
             << CopiaConexionesEntrantes.top().nombre_origen << " | "
             << CopiaConexionesEntrantes.top().ip_destino << " | "
             << CopiaConexionesEntrantes.top().puerto_destino << " | "
             << CopiaConexionesEntrantes.top().nombre_destino << endl;

        // Borra la conexion top
        CopiaConexionesEntrantes.pop();
    }
}

// Imprimir conexiones salientes
void ConexionesComputadora::imprimir_ConexionesSalientes()
{
    queue<Entry> CopiaConexionesSalientes = ConexionesSalientes;

    cout << endl;
    while (!CopiaConexionesSalientes.empty())
    {
        // Imprime conexion front
        cout << CopiaConexionesSalientes.front().fecha << " | "
             << CopiaConexionesSalientes.front().hora << " | "
             << CopiaConexionesSalientes.front().ip_origen << " | "
             << CopiaConexionesSalientes.front().puerto_origen << " | "
             << CopiaConexionesSalientes.front().nombre_origen << " | "
             << CopiaConexionesSalientes.front().ip_destino << " | "
             << CopiaConexionesSalientes.front().puerto_destino << " | "
             << CopiaConexionesSalientes.front().nombre_destino << endl;

        // Borra la conexion top
        CopiaConexionesSalientes.pop();
    }
}

// Mostrar la ultima conexión entrante
void ConexionesComputadora::ultimaConexionEntrante()
{
    cout << endl;
    cout << "Ultima conexion entrante: " << endl;

    cout << ConexionesEntrantes.top().fecha << " | " 
    << ConexionesEntrantes.top().hora << " | " 
    << ConexionesEntrantes.top().ip_origen << " | " 
    << ConexionesEntrantes.top().puerto_origen << " | " 
    << ConexionesEntrantes.top().nombre_origen << " | " 
    << ConexionesEntrantes.top().ip_destino << " | " 
    << ConexionesEntrantes.top().puerto_destino << " | " 
    << ConexionesEntrantes.top().nombre_destino << endl;
}

// Mostrar la longitud de conexiones entrantes
void ConexionesComputadora::longitudEntrantes()
{
    cout << endl;
    cout << "Longitud de conexiones entrantes: " << ConexionesEntrantes.size() << endl;
}

// Mostrar la longitud de conexiones salientes
void ConexionesComputadora::longitudSalientes()
{
    cout << endl;
    cout << "Longitud de conexiones salientes: " << ConexionesSalientes.size() << endl;
}

// Extra: Revisar si hay 3 conexiones salientes seguidas a un mismo sitio web
void ConexionesComputadora::conexionesSeguidas()
{
    // Se crea copia de conexiones salientes para poder iterar sin modificar original
    queue<Entry> CopiaConexionesSalientes = ConexionesSalientes;

    // Se crean variables que contengan las dos ips de sitios web anteriores
    string ip_1 = "";
    string ip_2 = "";

    // Iteración sobre cada conexion saliente
    while (!CopiaConexionesSalientes.empty())
    {
        // Si la conexion saliente actual fue a los puertos 80 o 443 es porque fue a sitio web
        if (CopiaConexionesSalientes.front().puerto_destino == "80" || CopiaConexionesSalientes.front().puerto_destino == "443")
        {
            // Comprueba si el actual es igual a los últimas dos conexiones
            if (CopiaConexionesSalientes.front().ip_destino == ip_2 && CopiaConexionesSalientes.front().ip_destino == ip_1)
            {
                cout << endl;
                cout << "Se hicieron 3 conexiones salientes seguidas a sitios web a esta direccion IP: " << endl;
                cout << CopiaConexionesSalientes.front().fecha << " | "
                     << CopiaConexionesSalientes.front().hora << " | "
                     << CopiaConexionesSalientes.front().ip_origen << " | "
                     << CopiaConexionesSalientes.front().puerto_origen << " | "
                     << CopiaConexionesSalientes.front().nombre_origen << " | "
                     << CopiaConexionesSalientes.front().ip_destino << " | "
                     << CopiaConexionesSalientes.front().puerto_destino << " | "
                     << CopiaConexionesSalientes.front().nombre_destino << endl;

                break; // Cuando encuentre 3 conexiones seguidas salir del ciclo
            }
        }
        // Desplaza las direcciones IP para siguiente iteracion
        ip_1 = ip_2;
        ip_2 = CopiaConexionesSalientes.front().ip_destino;

        // Muevete al siguiente eliminando el front
        CopiaConexionesSalientes.pop();
    }
}
