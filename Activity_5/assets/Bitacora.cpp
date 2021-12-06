#include "Bitacora.hpp"
#include <iostream>

// El constructor recibe el nombre der archivo y carga los datos a los vectores
Bitacora::Bitacora(string _file_name)
{
    // Cargar el vector de entradas con todas las filas del csv
    file_name = _file_name;
    LoadData();

    // Cargar las estructuras de datos
    loadEstructuras();
}

// Carga de los datos del csv a los vectores
void Bitacora::LoadData()
{
    ifstream data_file;
    data_file.open(file_name);
    string line, word;
    string column_data[7];

    while (getline(data_file, line))
    {
        stringstream ss(line);
        int i = 0;

        while (getline(ss, word, ','))
        {
            column_data[i] = word;
            i++;
        }

        string fecha = column_data[0];
        string hora = column_data[1];
        string ip_origen = column_data[2];
        string puerto_origen = column_data[3];
        string nombre_origen = column_data[4];
        string ip_destino = column_data[5];
        string puerto_destino = column_data[6];
        string nombre_destino = column_data[7];

        Entry currentEntry(fecha, hora, ip_origen, puerto_origen, nombre_origen, ip_destino, puerto_destino, nombre_destino);

        entries.push_back(currentEntry);
    }

    total_entries = entries.size();
}

// Imprime la informacion de los vectores
void Bitacora::print()
{
    for (int i = 0; i < 30; i++)
    {
        cout << entries[i].fecha << " | " << entries[i].hora << " | " << entries[i].ip_origen << " | " << entries[i].puerto_origen << " | " << entries[i].nombre_origen << " | " << entries[i].ip_destino << " | " << entries[i].puerto_destino << " | " << entries[i].nombre_destino << endl;
    }
}

// Contar cantidad de registros del día especificado
void Bitacora::countRegistersInADay(int searchedDay)
{
    int actualDay = 1;        // Numero de día actual, inicia en el día 1
    int registersCounter = 0; // Contador de registros del día buscado
    int i = 0;                // Iterador
    string searchedDayValue;  // Valor de fecha del día buscado

    // Mientras que el día actual no sea mayor que el numero de día siguiente del buscado o llegue al final
    while (actualDay < searchedDay + 1 && i < total_entries)
    {
        // Si la fecha del día siguiente es mayor a la del dia actual entonces vamos a cambiar a un nuevo día
        if (entries[i].fecha < entries[i + 1].fecha)
        {
            actualDay++; // Aumenta el numero de dia actual
        }

        // Si el día en el que estamos es igual al dia buscado suma al contador
        if (actualDay == searchedDay)
        {
            registersCounter++;
            searchedDayValue = entries[i].fecha;
        }
        i++;
    }

    cout << "Dia Seleccionado (" << searchedDay << "): " << searchedDayValue << endl;
    cout << "Total de Registros en Dia (" << searchedDay << "): " << registersCounter << endl;
}

// Busca un nombre en especifico dentro del vector nombre de origen
void Bitacora::searchByName(string nombres[], int nombresSize)
{
    // Para cada nombre
    for (int i = 0; i < nombresSize; i++)
    {
        int j = 0;                                      //Iterador
        bool nameFounded = false;                       // Bool que marca si ya se encontró el nombre
        string searchedName = nombres[i] + ".reto.com"; // Nombre buscado

        // Si aún no se ha encontrado el nombre y aún no se recorre todo el vector
        while (!nameFounded && j < total_entries)
        {
            if (searchedName == entries[j].nombre_origen)
            {
                cout << nombres[i] << ": SI esta en la lista" << endl;
                nameFounded = true;
            }
            j++;
        }

        if (!nameFounded)
        {
            cout << nombres[i] << ": NO esta en la lista" << endl;
        }
    }
}

// Buscar nombre de computadora
void Bitacora::searchByMail()
{
    for (int j = 0; j < total_entries; j++)
    {
        if (entries[j].nombre_destino == "server.reto.com")
        {
            cout << "Se encontro a: " << entries[j].nombre_destino << endl;
            break; // Si se encuentra sale del ciclo
        }
    }
}

// Encuentra e imprime todos los servicios de mensajería usados
void Bitacora::findAllMails()
{
    vector<string> emails;
    bool repeatedEmail = false;

    cout << endl;
    cout << "Correos: " << endl;

    for (int i = 0; i < total_entries; i++)
    {
        // Si el nombre esta registrado correctamente
        if (entries[i].nombre_destino != "-")
        {
            // Para cada email registrado en el vector emails
            for (int j = 0; j < emails.size(); j++)
            {
                // Si el nombre del correo ya esta dentro del vector correo
                if (entries[i].nombre_destino == emails[j])
                {
                    repeatedEmail = true; // Marca que ese correo ya esta en el vector
                    break;                // Deja de comparar con los siguientes correos
                }
            }

            // Si al final de compara con todos los correos no estaba en la lista
            if (!repeatedEmail)
            {
                cout << "- " << entries[i].nombre_destino << endl; // Imprime el correo nuevo
                emails.push_back(entries[i].nombre_destino);       // Añade el nuevo correo a la lista
            }

            repeatedEmail = false; // Regresa valor a falso para siguiente ciclo
        }
    }
}

// Se cargan las estructuras de datos iterando sobre las entradas
void Bitacora::loadEstructuras()
{
    // Iteramos sobre las entradas
    for (int i = 0; i < entries.size(); i++)
    {
        // Carga de conjunto dominiosExternos con todos los nombres de dominios en el csv

        // Agrega el nombre origen si no termina en .reto.com
        if (entries[i].nombre_origen.size() < 9 ||
            entries[i].nombre_origen.substr(entries[i].nombre_origen.size() - 9, 9) != ".reto.com")
        {
            dominiosExternos.insert(entries[i].nombre_origen);
        }

        // Agrega el nombre destino si no termina en .reto.com
        if (entries[i].nombre_destino.size() < 9 ||
            entries[i].nombre_destino.substr(entries[i].nombre_destino.size() - 9, 9) != ".reto.com")
        {
            dominiosExternos.insert(entries[i].nombre_destino);
        }

        // Carga del mapa de dominioAIp con todos los dominios y sus ips

        // Agregar un par de nombre de dominio y su ip por cada entrada
        dominiosAIps[entries[i].nombre_origen] = entries[i].ip_origen;
        dominiosAIps[entries[i].nombre_destino] = entries[i].ip_destino;

        // Carga del mapa de ipADominio con todas las ips y sus dominios

        // Agregar un par de nombre de dominio y su ip por cada entrada
        ipsADominios[entries[i].ip_origen] = entries[i].nombre_origen;
        ipsADominios[entries[i].ip_destino] = entries[i].nombre_destino;

        // Carga del mapa de ipsAConexiones con todos las ips y sus conexiones

        // Agregar la conexion saliente a la ip correspondiente
        ipsAConexiones[entries[i].ip_origen].conexionesSalientes.push_back(entries[i]);

        // Agregar la conexion entrante a la ip correspondiente
        ipsAConexiones[entries[i].ip_destino].conexionesEntrantes.push_back(entries[i]);
    }
}

// Calcula cantidad de ips de dominio reto.com que tienen al menos una conexion entrante
int Bitacora::ipsInternasConEntrantes()
{
    // Contador
    int counter = 0;

    // Se itera sobre los pares del mapa
    for (auto const &pair : ipsAConexiones)
    {
        // Si la ip empieza con los primeros 9 números de la red interna y sus conexiones entrantes son más grandes que 0
        if (pair.first.substr(0, 11) == "192.168.144" && pair.second.conexionesEntrantes.size() > 0)
            counter++;
    }

    return counter;
}

// Obtener las ips unicas de las conexiones entrantes de algunas computadoras de la red interna
void Bitacora::obtenerIpsConexionesEntrantes()
{
    int counter = 0; // Contdor de cantidad de ips seleccionadas

    // Iterar sobre el mapa de ipsADominios para seleccionar 10 primeras ips coincidentes
    for (auto const &pair : ipsADominios)
    {
        string ip = pair.first;       // Ip actual
        string dominio = pair.second; // Dominio actual

        if (ip.substr(0, 11) == "192.168.144" &&                              // Si la ip es de la red interna
            dominio != "server.reto.com" &&                                   // Si el dominio es diferente de server.reto.com
            ipsAConexiones[ip].conexionesEntrantes.size() > 0 &&              // Si la ip tiene al menos 1 conexion entrante
            ipsAConexiones[ip].conexionesEntrantes[0].puerto_destino != "67") // Si el puerto de la ip no es DHCP
        {
            ipsSeleccionadas.push_back(ip); // Seleccionar la ip
            counter++;                      // Aumentar cantidad de ips seleccionadas
        }

        //Salir del ciclo al seleccionar 10 ips
        if (counter == 10)
            break;
    }

    // Llenar set de las ips unicas de las conexiones entrantes de las ips seleccionadas
    for (int i = 0; i < ipsSeleccionadas.size(); i++)
    {
        // Iterar sobre las conexiones entrantes de la ip seleccionada y agregar la ip entrante
        for (int j = 0; j < ipsAConexiones[ipsSeleccionadas[i]].conexionesEntrantes.size(); j++)
        {
            ipsConexionesEntrantesSeleccionadas.insert(ipsAConexiones[ipsSeleccionadas[i]].conexionesEntrantes[j].ip_origen);
        }
    }

    // Imprimir las ips unicas de las conexiones entrantes de las ips seleccionadas
    cout << endl;
    cout << "Ips de las conexiones entrantes de las computadoras seleccionadas: " << endl;
    set<string>::iterator itr;
    for (itr = ipsConexionesEntrantesSeleccionadas.begin(); itr != ipsConexionesEntrantesSeleccionadas.end(); itr++)
    {
        cout << *itr << endl;
    }
}

// Deteminar si las ips unicas de las conexiones entrantes se han comunicado con el dominio extraño
void Bitacora::comunicacionConDominioExtano()
{
    string dominioExtrano1 = "27o7wwa6btayxreesf1h.org"; // Dominio extraño 1
    string dominioExtrano2 = "9o7i94oyprais2lpcztv.com"; // Dominio extraño 2

    // Iteramos sobre las ips unicas de las conexiones entrantes de las ips seleccionadas
    set<string>::iterator itr;
    for (itr = ipsConexionesEntrantesSeleccionadas.begin(); itr != ipsConexionesEntrantesSeleccionadas.end(); itr++)
    {
        bool founded = false; // Marca si se encontró comunicación

        // Se itera sobre las conexiones entrantes de la ip actual
        for (int i = 0; i < ipsAConexiones[*itr].conexionesEntrantes.size(); i++)
        {
            // Si el dominio entrante es igual a dominios extraños
            if (ipsAConexiones[*itr].conexionesEntrantes[i].nombre_origen == dominioExtrano1 ||
                ipsAConexiones[*itr].conexionesEntrantes[i].nombre_origen == dominioExtrano2)
            {
                founded = true;
                break;
            }
        }

        // Se itera sobre las conexiones salientes de la ip actual
        for (int i = 0; i < ipsAConexiones[*itr].conexionesSalientes.size(); i++)
        {
            // Si el dominio saliente es igual a dominios extraños
            if (ipsAConexiones[*itr].conexionesSalientes[i].nombre_destino == dominioExtrano1 ||
                ipsAConexiones[*itr].conexionesSalientes[i].nombre_destino == dominioExtrano2)
            {
                founded = true;
                break;
            }
        }

        // Si ha habido una comunicación con el dominios extraños
        if (founded)
        {
            conexionesADominioExtrano.push_back(*itr);
        }
    }

    // Imprimir computadoras que tuvieron comunicación con dominios extraños
    cout << endl;
    cout << "Computadoras que tuvieron comunicacion con dominios extranos: " << endl;
    for (int i = 0; i < conexionesADominioExtrano.size(); i++)
    {
        cout << conexionesADominioExtrano[i] << endl;
    }
}

// Mostrar datos de las primeras conexiones entre las compuadoras y el dominio extraño
void Bitacora::datosDeComunicacion()
{
    vector<string> dominiosExtranos = {"27o7wwa6btayxreesf1h.org", "9o7i94oyprais2lpcztv.com"}; // Dominios extraños

    // Iteramos sobre los dominios extraños
    cout << endl;
    for (int h = 0; h < dominiosExtranos.size(); h++)
    {
        // Iterar sobre las computadoras que se comunicaron con un dominio extraño
        for (int i = 0; i < conexionesADominioExtrano.size(); i++)
        {
            // Iterar sobre sus conexiones entrantes
            for (int j = 0; j < ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes.size(); j++)
            {
                // Si se encuentera que el dominio entrante es el dominio extraño
                if (ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes[j].nombre_origen == dominiosExtranos[h])
                {
                    // Determinar protocolo
                    string protocolo;
                    if (ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes[j].puerto_destino == "443")
                        protocolo = "HTTPS";
                    else if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].puerto_destino == "965")
                        protocolo = "TCP";
                    else
                        protocolo = "Otro";

                    // Imprimir información
                    cout << "Primera conexion entre "
                         << dominiosExtranos[h]
                         << " -> " << conexionesADominioExtrano[i]
                         << " | Fecha: " << ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes[j].fecha
                         << " | Hora: " << ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes[j].hora
                         << " | Protocolo: " << protocolo << endl;

                    break;
                }
            }

            // Iterar sobre sus conexiones salientes
            for (int j = 0; j < ipsAConexiones[conexionesADominioExtrano[i]].conexionesSalientes.size(); j++)
            {
                // Si se encuentera que el dominio saliente es el dominio extraño
                if (ipsAConexiones[conexionesADominioExtrano[i]].conexionesSalientes[j].nombre_destino == dominiosExtranos[h])
                {
                    // Determinar protocolo
                    string protocolo;
                    if (ipsAConexiones[conexionesADominioExtrano[i]].conexionesEntrantes[j].puerto_destino == "443")
                        protocolo = "HTTPS";
                    else if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].puerto_destino == "965")
                        protocolo = "TCP";
                    else
                        protocolo = "Otro";

                    // Imprimir información
                    cout << "Primera conexion entre "
                         << conexionesADominioExtrano[i]
                         << " -> " << dominiosExtranos[h]
                         << " | Fecha: " << ipsAConexiones[conexionesADominioExtrano[i]].conexionesSalientes[j].fecha
                         << " | Hora: " << ipsAConexiones[conexionesADominioExtrano[i]].conexionesSalientes[j].hora
                         << " | Protocolo: " << protocolo << endl;

                    break;
                }
            }
        }
    }

    /*
    PASO EXTRA: Como nuestro csv tiene errores y en muchas filas el dominio extraño lo tiene en la
    columna de ip y no la columna de dominio en este paso se va a buscar la primer conexión entre la ip con el 
    nombre dominio raro y las computadoras con conexiones a el dominio extraño
    */

    cout << endl;
    cout << "PASO EXTRA: Buscar conexiones entre computadora con ip igual al dominio raro y computadoras que se comunicaron con dominio extranos." << endl;

    // Iterar sobre las computadoras que se comunicaron con un dominio extraño
    for (int i = 0; i < conexionesADominioExtrano.size(); i++)
    {
        // Iterar sobre las conexiones entrantes de la ip con el nombre del dominio extraño
        for (int j = 0; j < ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes.size(); j++)
        {
            // Si se encuentera que la ip entrante es la ip de la computadora actual
            if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].ip_origen == conexionesADominioExtrano[i])
            {
                // Determinar protocolo
                string protocolo;
                if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].puerto_destino == "443")
                    protocolo = "HTTPS";
                else if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].puerto_destino == "965")
                    protocolo = "TCP";
                else
                    protocolo = "Otro";

                // Imprimir información
                cout << "Primera conexion entre "
                     << conexionesADominioExtrano[i]
                     << " -> "
                     << "27o7wwa6btayxreesf1h.org"
                     << " | Fecha: " << ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].fecha
                     << " | Hora: " << ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].hora
                     << " | Protocolo: " << protocolo << endl;

                break;
            }
        }

        // Iterar sobre las conexiones salientes de la ip con el nombre del dominio extraño
        for (int j = 0; j < ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesSalientes.size(); j++)
        {
            // Si se encuentera que la ip saliente es la ip de la computadora actual
            if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesSalientes[j].ip_destino == conexionesADominioExtrano[i])
            {
                // Determinar protocolo
                string protocolo;
                if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesSalientes[j].puerto_destino == "443")
                    protocolo = "HTTPS";
                else if (ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesEntrantes[j].puerto_destino == "965")
                    protocolo = "TCP";
                else
                    protocolo = "Otro";

                // Imprimir información
                cout << "Primera conexion entre "
                     << "27o7wwa6btayxreesf1h.org"
                     << " -> "
                     << conexionesADominioExtrano[i]
                     << " | Fecha: " << ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesSalientes[j].fecha
                     << " | Hora: " << ipsAConexiones["27o7wwa6btayxreesf1h.org"].conexionesSalientes[j].hora
                     << " | Protocolo: " << protocolo << endl;

                break;
            }
        }
    }
    cout << endl;
}