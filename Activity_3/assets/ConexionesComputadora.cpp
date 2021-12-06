#include "ConexionesComputadora.hpp"
#include "TreeNode.hpp"
#include "BST.hpp"
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <typeinfo>

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

// Ver cantidad de conexiones en un día con un mapa
map<string, int> ConexionesComputadora::conexionesPorDia(string day)
{
    map<string, int> frecuencias;

    // Iteramos sobre conexiones
    for (int i = 0; i < entries.size(); i++)
    {
        // Posicionarse en la fecha indicada
        if (entries[i].fecha.substr(0, 2) == day)
        {
            // Si la direccion desino es diferente de - y no incluye reto.com
            if (entries[i].nombre_destino != "-" && entries[i].nombre_destino.find("reto.com") == std::string::npos)
            {
                frecuencias[entries[i].nombre_destino]++;
            }
        }

        // Si estamos en una fecha superior a la indicada termina el ciclo
        if (stoi(entries[i].fecha.substr(0, 2)) == stoi(day) + 1)
        {
            break;
        }
    }

    return frecuencias;
}

// Mostrar el top N de conexiones por día
vector<TreeNode<int> *> ConexionesComputadora::topConexionesPorDia(int n, string day)
{
    // Crear BST
    BST<int> *bst = new BST<int>();

    // Recibir mapa de frecuencias
    map<string, int> frecuencias = conexionesPorDia(day);

    // Insertar elementos del mapa en el BST
    auto item = frecuencias.begin();
    while (item != frecuencias.end())
    {
        // Se crea un nodo con el valor numérico y el nombre del sitio y se agrega al bst
        TreeNode<int> *node = new TreeNode<int>(item->second, item->first);
        bst->insert(node);
        ++item;
    }

    // Crear un vector que contenga los nodos de mayor a menor
    vector<TreeNode<int> *> top = bst->reverseInOrden();

    // Crear un vector que almacene solo el top N
    vector<TreeNode<int> *> topN;

    // Imprimir top N
    cout << endl;
    cout << "Top " << n << " del dia " << day << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". " << top[i]->getNombre() << " - " << top[i]->getInfo() << endl;
        topN.push_back(top[i]);
    }

    // Regresar el vector top N
    return topN;
}

// Mostrar si hubo un sitio que estuviera en el top 5 todos los días
void ConexionesComputadora::top5TodosLosDias()
{
    // Vector que contiene todos los días
    string days[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"};

    // Matriz que contendrá los tops 5 de cada día
    vector<vector<TreeNode<int> *>> top_register;

    // Vector que contendrá los sitios que se repitieron todos los días
    vector<string> reapeated_registers;

    // Cargar los tops 5 de todos los días en la matriz
    for (int i = 0; i < 10; i++)
    {
        top_register.push_back(this->topConexionesPorDia(5, days[i]));
    }

    // Para cada valor del primer top 5 de la matriz
    for (int i = 0; i < 5; i++)
    {
        string registro = top_register[0][i]->getNombre(); // Valor actual
        int times_founded = 0;                             // Cantidad de veces encontrado

        // Para cada siguiente vector de tops
        for (int j = 1; j < top_register.size(); j++)
        {
            // Para cada valor de los tops siguientes
            for (int k = 0; k < 5; k++)
            {
                // Si el valor actual se encuentra en dentro del vector actual suma el contador
                if (top_register[j][k]->getNombre() == registro)
                {
                    times_founded += 1;
                }
            }
        }

        // Añadir al vector si el valor se encontró en los 9 días siguientes
        if (times_founded == 9)
        {
            reapeated_registers.push_back(registro);
        }
    }

    // Imprimir los nombres de los sitios que estuvieron todos los días
    cout << endl;
    cout << "Registros repetidos todos los dias: " << endl;
    for (int i = 0; i < reapeated_registers.size(); i++)
    {
        cout << reapeated_registers[i] << endl;
    }
}

// Mostrar si hubo un sitio que estuviera en el top a partir de un día
void ConexionesComputadora::top5APartirDeUnDia()
{
    // Vector que contiene todos los días
    string days[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"};

    // Matriz que contendrá los tops 5 de cada día
    vector<vector<TreeNode<int> *>> top_register;

    // Vector que contendrá los sitios que se repitieron todos los días
    vector<string> reapeated_registers;

    // Cargar los tops 5 de todos los días en la matriz
    for (int i = 0; i < 10; i++)
    {
        top_register.push_back(this->topConexionesPorDia(5, days[i]));
    }

    // Para cada vector menos el final
    for (int h = 0; h < top_register.size() - 1; h++)
    {
        // Para cada elemento de cada vector
        for (int i = 0; i < 5; i++)
        {
            string registro = top_register[h][i]->getNombre(); // Valor actual
            int times_founded = 0;                             // Cantidad de veces encontrado

            // Para cada siguiente vector de tops
            for (int j = h + 1; j < top_register.size(); j++)
            {
                // Para cada valor de los siguientes vectores
                for (int k = 0; k < 5; k++)
                {
                    // Si el valor actual se encuentra en dentro del vector actual suma el contador
                    if (top_register[j][k]->getNombre() == registro)
                    {
                        times_founded += 1;
                    }
                }
            }

            // Añadir al vector si el valor se encontró en el número de días siguientes
            if (times_founded == 9 - h)
            {
                reapeated_registers.push_back(registro);
            }
        }
    }

    /* 
    Hasta ahora se tiene un vector con los valores de los sitios repetidos
    por cada nivel en el que se empezaron a repetir entonces se limpiará para
    que solo se repitan los nombres una vez
    */

    // Vector que contendrá los nombres solo una vez
    vector<string> clean_reapeated_registers;

    // Para cada sitio
    for (int i = 0; i < reapeated_registers.size(); i++)
    {
        bool alreadyIn = false; // Indicador si el sitio ya está en el vector limpio

        // Para cada sitio en el vector limpio
        for (int j = 0; j < clean_reapeated_registers.size(); j++)
        {
            // Si el valor del sitio actual es igual al valor del vector limpio es porque ya estaba
            if (reapeated_registers[i] == clean_reapeated_registers[j])
            {
                alreadyIn = true; // Se marca que ya estaba en el vector
                break;            // Se termina el ciclo
            }
        }

        // Si el sitio actual no estaba en el vector limpio agregalo
        if (!alreadyIn)
        {
            clean_reapeated_registers.push_back(reapeated_registers[i]);
        }
    }

    // Imprime los sitios que se repitieron a partir de un día
    cout << endl;
    cout << "Registros repetidos a partir de un dia: " << endl;
    for (int i = 0; i < clean_reapeated_registers.size(); i++)
    {
        cout << clean_reapeated_registers[i] << endl;
    }
}

// Mostrar conexiones más altas de lo normal
void ConexionesComputadora::conexionMasAltaNormal()
{
    // Vector que contiene todos los días
    string days[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"};

    // Matriz que contendrá los tops 5 de cada día
    vector<vector<TreeNode<int> *>> top_register;

    // Cargar los tops 5 de todos los días en la matriz
    for (int i = 0; i < 10; i++)
    {
        top_register.push_back(this->topConexionesPorDia(5, days[i]));
    }

    // Vector que contiene el valor más alto por cada día
    vector<TreeNode<int> *> top1_registers;

    float average = 0;    // Promedio de los valores
    int nodesCounter = 0; // Cantidad de nodos para sacar promedio

    // Obtener los nodos con valor más alto de cada día
    for (int i = 0; i < top_register.size(); i++)
    {
        TreeNode<int> *max; // Valor maximo del día

        for (int j = 0; j < top_register[i].size(); j++)
        {
            TreeNode<int> *current = top_register[i][j]; // Se posiciona en el nodo actual

            average += current->getInfo(); // Se suman los valores para después sacar el promedio
            nodesCounter++;                // Se aumenta el contador para después sacar el promedio

            // En la primer iteración el valor maximo será el current
            if (j == 0)
            {
                max = current;
            }
            else
            {
                // Si el valor current es mayor al máximo cambia el max al current
                if (current->getInfo() > max->getInfo())
                {
                    max = current;
                }
            }
        }

        // Se agrega el valor máximo del día al vector
        top1_registers.push_back(max);
    }

    // Calculamos promedio de los datos
    average = average / nodesCounter;

    // Imprimir los nodos que tengan un valor mayor al normal
    cout << endl;
    cout << "Sitios con cantidad de conexiones mayores de lo normal: " << endl;
    for (int i = 0; i < top1_registers.size(); i++)
    {
        // Si el valor del nodo es mayor que 3 veces el promedio entonces es un valor más alto de lo normal y se imprime
        if (top1_registers[i]->getInfo() > average * 3)
        {
            cout << "Dia " << days[i] << " - " << top1_registers[i]->getNombre() << " - " << top1_registers[i]->getInfo() << endl;
        }
    }
}
