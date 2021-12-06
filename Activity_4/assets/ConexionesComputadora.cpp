#include "ConexionesComputadora.hpp"
#include "BST.hpp"
#include <stack>
#include <queue>

using namespace std;

// Constructor
ConexionesComputadora::ConexionesComputadora(vector<Entry> &_entries)
{
    entries = _entries;
    get_ip();                              // Se crea el ip interna
    nombre_alta = conexionMasAltaNormal(); // Se obtiene el nombre de sitio alto
    cargar_Datos();                        // Se cargan datos

    // Imprimir ips
    cout << endl;
    cout << "IP Interna: " << ip_interna << endl;
    cout << "IP Extrana: " << ip_extrana << endl;
    cout << "IP Alta: " << ip_alta << endl;
}

// Crear ip de equipo con numero ingresado
void ConexionesComputadora::get_ip()
{
    string number;

    // Se ingresa numero entre 1 a 150
    cout << endl;
    cout << "Ingresa el ultimo numero de tu direccion de ip (1-150): ";
    cin >> number;

    string incomplete_ip = "192.168.144";

    // Se crea ip de equipo
    ip_interna = incomplete_ip + "." + number;
}

// Cargar conexiones entrantes
void ConexionesComputadora::cargar_Datos()
{
    // Iterar sobre todos los registros
    for (int i = 0; i < entries.size(); i++)
    {
        // Conexiones Entrantes
        if (entries[i].ip_destino == ip_interna)
        {
            ConexionesEntrantes.push(entries[i]);
        }

        // Conexiones Salientes
        if (entries[i].ip_origen == ip_interna)
        {
            nombre_interna = entries[i].nombre_origen; // Indica el nombre del equipo
            ConexionesSalientes.push(entries[i]);
        }

        // IP Extraña - Si el nombre destino termina en .gov
        if (entries[i].ip_destino.size() > 4 && entries[i].ip_destino.substr(entries[i].ip_destino.size() - 4, 4) == ".org")
        {
            ip_extrana = entries[i].ip_destino;
        }

        // IP Alta - Si el nombre destino es igual al nombre de conexion alta
        if (entries[i].nombre_destino == nombre_alta)
        {
            ip_alta = entries[i].ip_destino;
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
    for (int i = 0; i < n; i++)
    {
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
string ConexionesComputadora::conexionMasAltaNormal()
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

    // Regresar el nombre de un nodo que tenga un valor mayor al normal
    for (int i = 0; i < top1_registers.size(); i++)
    {
        // Si el valor del nodo es mayor que 3 veces el promedio entonces es un valor más alto de lo normal y se regresa
        if (top1_registers[i]->getInfo() > average * 3)
        {
            return top1_registers[i]->getNombre();
        }
    }
}

// Cargar los mapas de grafos por día
void ConexionesComputadora::cargarGrafos()
{
    // Inizializar los grafos del mapa de grafos
    string dias[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"}; // Vector que contiene todos los días
    for (int i = 0; i < 10; i++)
    {
        Graph<string, int> grafo; // Grafo vacío

        // Agregar un par los mapas donde la llave será el día y el contenido será un grafo
        MapaGrafosRedInterna[dias[i]] = grafo;
        MapaGrafosSitiosWeb[dias[i]] = grafo;
    }

    // Iterar sobre todos los registros
    for (int i = 0; i < entries.size(); i++)
    {
        string dia = entries[i].fecha.substr(0, 2); // Obtenemos el día de la entrada en string

        // Grafo Conexiones de Red Interna - Si la ip origen y destino estan en la red interna
        if (entries[i].ip_origen.substr(0, 11) == "192.168.144" && entries[i].ip_destino.substr(0, 11) == "192.168.144")
        {
            Vertex<string, int> *source; // Vector origen
            Vertex<string, int> *target; // Vector objetivo

            // Busca en los nodos los vértices source y target
            bool sourceFounded = false;
            bool targetFounded = false;

            for (int j = 0; j < MapaGrafosRedInterna[dia].nodes.size(); j++)
            {
                // Si la ip del vértice es igual a la ip de la entrada origen actual
                if (MapaGrafosRedInterna[dia].nodes[j]->getInfo() == entries[i].ip_origen)
                {
                    source = MapaGrafosRedInterna[dia].nodes[j]; // Indica que este vertice es el orígen
                    sourceFounded = true;
                }

                // Si la ip del vértice es igual a la ip de la entrada destino actual
                if (MapaGrafosRedInterna[dia].nodes[j]->getInfo() == entries[i].ip_destino)
                {
                    target = MapaGrafosRedInterna[dia].nodes[j]; // Indica que este vertice es el objetivo
                    targetFounded = true;
                }

                // Si ya se encontraron los dos sal del ciclo
                if (sourceFounded && targetFounded)
                    break;
            }

            // Si no se encontró ningún vértice con la ip la entrada origen actual
            if (!sourceFounded)
            {
                // Crear vertice y agregalo a los nodos
                Vertex<string, int> *a = new Vertex<string, int>(entries[i].ip_origen);
                MapaGrafosRedInterna[dia].addVertex(a); // Agregalo al grafo
                source = a;                             // Indica que este vértice es el orígen
            }

            // Si no se encontró ningún vértice con la ip de la entrada destino actual
            if (!targetFounded)
            {
                // Crear vertice y agregalo a los nodos
                Vertex<string, int> *b = new Vertex<string, int>(entries[i].ip_destino);
                MapaGrafosRedInterna[dia].addVertex(b); // Agregalo al grafo
                target = b;                             // Indica que este vértice es el objetivo
            }

            // Buscar en los edges del vértice source si ya hay un edge al vértice target
            bool edgeFounded = false;

            for (int j = 0; j < source->edges.size(); j++)
            {
                // Si la ip del vértice objetivo del edge actual es igual a la ip del vertice target
                if (source->edges[j]->getTarget()->getInfo() == target->getInfo())
                {
                    edgeFounded = true;
                    break;
                }
            }

            // Si todavía no había un edge al vértice target entonces crealo
            if (!edgeFounded)
            {
                // Agrega el vértice
                Edge<string, int> *new_edge = new Edge<string, int>(1, target);
                source->addEdge(new_edge);

                source->conexionesSalientes++; // Suma las conexiones salientes del vértice source
                target->conexionesEntrantes++; // Suma las conexiones entrantes del vértice target
            }
        }

        // Grafo Conexiones a Sitios Web - Si el puerto origen o el destino son 80 o 443
        if (entries[i].puerto_origen == "443" || entries[i].puerto_origen == "80" ||
            entries[i].puerto_destino == "443" || entries[i].puerto_destino == "80")
        {
            Vertex<string, int> *source; // Vector origen
            Vertex<string, int> *target; // Vector objetivo

            // Busca en los nodos los vértices source y target
            bool sourceFounded = false;
            bool targetFounded = false;

            for (int j = 0; j < MapaGrafosSitiosWeb[dia].nodes.size(); j++)
            {
                // Si la ip del vértice es igual a la ip de la entrada origen actual
                if (MapaGrafosSitiosWeb[dia].nodes[j]->getInfo() == entries[i].ip_origen)
                {
                    source = MapaGrafosSitiosWeb[dia].nodes[j]; // Indica que este vertice es el orígen
                    sourceFounded = true;
                }

                // Si la ip del vértice es igual a la ip de la entrada destino actual
                if (MapaGrafosSitiosWeb[dia].nodes[j]->getInfo() == entries[i].ip_destino)
                {
                    target = MapaGrafosSitiosWeb[dia].nodes[j]; // Indica que este vertice es el objetivo
                    targetFounded = true;
                }

                // Si ya se encontraron los dos sal del ciclo
                if (sourceFounded && targetFounded)
                    break;
            }

            // Si no se encontró ningún vértice con la ip la entrada origen actual
            if (!sourceFounded)
            {
                // Crear vertice y agregalo a los nodos
                Vertex<string, int> *a = new Vertex<string, int>(entries[i].ip_origen);
                MapaGrafosSitiosWeb[dia].addVertex(a); // Agregalo al grafo
                source = a;                            // Indica que este vértice es el orígen
            }

            // Si no se encontró ningún vértice con la ip de la entrada destino actual
            if (!targetFounded)
            {
                // Crear vertice y agregalo a los nodos
                Vertex<string, int> *b = new Vertex<string, int>(entries[i].ip_destino);
                MapaGrafosSitiosWeb[dia].addVertex(b); // Agregalo al grafo
                target = b;                            // Indica que este vértice es el objetivo
            }

            // Buscar en los edges del vértice source si ya hay un edge al vértice target
            bool edgeFounded = false;

            for (int j = 0; j < source->edges.size(); j++)
            {
                // Si la ip del vértice objetivo del edge actual es igual a la ip del vertice target
                if (source->edges[j]->getTarget()->getInfo() == target->getInfo())
                {
                    edgeFounded = true;
                    break;
                }
            }

            // Si todavía no había un edge al vértice target entonces crealo
            if (!edgeFounded)
            {
                // Agrega el vértice
                Edge<string, int> *new_edge = new Edge<string, int>(1, target);
                source->addEdge(new_edge);

                source->conexionesSalientes++; // Suma las conexiones salientes del vértice source
                target->conexionesEntrantes++; // Suma las conexiones salientes del vértice target
            }
        }
    }
}

// Determina la cantidad de conexiones de A por día
void ConexionesComputadora::ConexionesDeAPorDia(bool mostrarEntrantes)
{
    string dias[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"}; // Vector que contiene todos los días

    // Si la opcion indica mostrar conexiones entrantes
    if (mostrarEntrantes)
    {
        // Para cada grafo dentro del mapa
        for (int i = 0; i < 10; i++)
        {
            int cantidadConexiones = 0;

            // Para cada vértice dentro del grafo
            for (int j = 0; j < MapaGrafosRedInterna[dias[i]].nodes.size(); j++)
            {
                if (MapaGrafosRedInterna[dias[i]].nodes[j]->getInfo() == ip_interna)
                {
                    cantidadConexiones = MapaGrafosRedInterna[dias[i]].nodes[j]->conexionesEntrantes;
                    break;
                }
            }

            // Imprimir cantidad de conexiones entrantes en el día actual
            cout << "Dia: " << dias[i] << " | Conexiones Entrantes: " << cantidadConexiones << endl;
        }
    }

    // Si la opcion indica mostrar conexiones salientes
    if (!mostrarEntrantes)
    {
        // Para cada grafo dentro del mapa
        for (int i = 0; i < 10; i++)
        {
            int cantidadConexiones = 0;

            // Para cada vértice dentro del grafo
            for (int j = 0; j < MapaGrafosRedInterna[dias[i]].nodes.size(); j++)
            {
                if (MapaGrafosRedInterna[dias[i]].nodes[j]->getInfo() == ip_interna)
                {
                    cantidadConexiones = MapaGrafosRedInterna[dias[i]].nodes[j]->conexionesSalientes;
                    break;
                }
            }

            // Imprimir cantidad de conexiones salientes en el día actual
            cout << "Dia: " << dias[i] << " | Conexiones Salientes: " << cantidadConexiones << endl;
        }
    }
}

// Determinar si A es el vértice con más conexiones salientes
void ConexionesComputadora::VerticeConMasConexionesSalientes()
{
    string dias[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"}; // Vector que contiene todos los días
    map<string, int> conexionesTotales;                                             // Mapa con la suma total de conexiones por vértice

    // Por cada grafo en el mapa
    for (int i = 0; i < 10; i++)
    {
        // Por cada vértice en el grafo
        for (int j = 0; j < MapaGrafosRedInterna[dias[i]].nodes.size(); j++)
        {
            // Suma a la llave con el nombre del vértce la cantidad de conexiones salientes de este día
            conexionesTotales[MapaGrafosRedInterna[dias[i]].nodes[j]->getInfo()] += MapaGrafosRedInterna[dias[i]].nodes[j]->conexionesSalientes;
        }
    }

    int conexionesSalientesIpInterna = conexionesTotales[ip_interna]; // Cantidad de conexiones salientes de A
    bool masGrande = true;                                            // Marcador para ver si las conexiones de A son las más grandes

    // Iteramos por los valores de suma de conexiones de cada vértice
    map<string, int>::iterator it;
    for (it = conexionesTotales.begin(); it != conexionesTotales.end(); it++)
    {
        // Si hay un valor de un vértice que es más grande que las conexiones de la red interna cambia el marcador
        if (it->second > conexionesSalientesIpInterna)
            masGrande = false;
    }

    // Imprime resultados
    if (masGrande)
        cout << "La ip interna es la que mas conexiones salientes tiene." << endl;
    else
        cout << "La ip interna no es la que mas conexiones salientes tiene." << endl;
}

// Determina la cantidad de conexiones entrantes a B por día
void ConexionesComputadora::ConexionesSitoB()
{
    string dias[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"}; // Vector que contiene todos los días

    // Para cada grafo dentro del mapa
    for (int i = 0; i < 10; i++)
    {
        int cantidadConexiones = 0;

        // Para cada vértice dentro del grafo
        for (int j = 0; j < MapaGrafosSitiosWeb[dias[i]].nodes.size(); j++)
        {
            if (MapaGrafosSitiosWeb[dias[i]].nodes[j]->getInfo() == ip_extrana)
            {
                cantidadConexiones = MapaGrafosSitiosWeb[dias[i]].nodes[j]->conexionesSalientes;
                break;
            }
        }

        // Imprimir cantidad de conexiones entrantes en el día actual
        cout << "Dia: " << dias[i] << " | Conexiones Entrantes: " << cantidadConexiones << endl;
    }
}

// Determina la cantidad de conexiones entrantes a C por día
void ConexionesComputadora::ConexionesSitoC()
{
    string dias[10] = {"10", "11", "12", "13", "14", "17", "18", "19", "20", "21"}; // Vector que contiene todos los días

    // Para cada grafo dentro del mapa
    for (int i = 0; i < 10; i++)
    {
        int cantidadConexiones = 0;

        // Para cada vértice dentro del grafo
        for (int j = 0; j < MapaGrafosSitiosWeb[dias[i]].nodes.size(); j++)
        {
            if (MapaGrafosSitiosWeb[dias[i]].nodes[j]->getInfo() == ip_alta)
            {
                cantidadConexiones = MapaGrafosSitiosWeb[dias[i]].nodes[j]->conexionesSalientes;
                break;
            }
        }

        // Imprimir cantidad de conexiones entrantes en el día actual
        cout << "Dia: " << dias[i] << " | Conexiones Entrantes: " << cantidadConexiones << endl;
    }
}