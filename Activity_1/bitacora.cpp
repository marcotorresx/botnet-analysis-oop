#include <iostream>
#include <vector>
#include <string>
#include "bitacora.hpp"

// El constructor recibe el nombre der archivo y carga los datos a los vectores
Bitacora::Bitacora(string _file_name)
{
    file_name = _file_name;
    LoadData();
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
        total_entries += 1;

        stringstream ss(line);
        int i = 0;

        while (getline(ss, word, ','))
        {
            column_data[i] = word;
            i++;
        }

        fecha.push_back(column_data[0]);
        hora.push_back(column_data[1]);
        ip_origen.push_back(column_data[2]);
        puerto_origen.push_back(column_data[3]);
        nombre_origen.push_back(column_data[4]);
        ip_destino.push_back(column_data[5]);
        puerto_destino.push_back(column_data[6]);
        nombre_destino.push_back(column_data[7]);
    }
}

// Imprime la informacion de los vectores
void Bitacora::print()
{
    for (int i = 0; i < 50; i++)
    {
        cout << fecha[i] << " | " << hora[i] << " | " << puerto_origen[i] << " | " << nombre_origen[i] << " | " << ip_destino[i] << " | " << puerto_destino[i] << " | " << nombre_destino[i] << endl;
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
        if (fecha[i] < fecha[i + 1])
        {
            actualDay++; // Aumenta el numero de dia actual
        }

        // Si el día en el que estamos es igual al dia buscado suma al contador
        if (actualDay == searchedDay)
        {
            registersCounter++;
            searchedDayValue = fecha[i];
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
            if (searchedName == nombre_origen[j])
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

// Busca cual es la direccion ip interna de la compañia
void Bitacora::SearchInternalIp()
{

    string substring;
    bool founded = false;                  // Marca si se ha encontrado la direccion para terminar funcion
    string ips[3] = {"192", "172", "10."}; // Los 3 primeros chars que puede tener una direccion ip interna

    // Para cada grupo de primeros caracteres
    for (int i = 0; i < 3; i++)
    {
        // Para cada direccion ip
        for (int j = 0; j < total_entries; j++)
        {
            substring = ip_destino[j].substr(0, 3); // Los primeros tres chars de la ip actual

            // Si sus primeros 3 chars son iguales
            if (ips[i] == substring)
            {
                cout << endl;
                cout << "Direccion interna: " << ip_destino[j] << endl;
                founded = true;
                break; // Termina el ciclo
            }
        }

        // Si se encuentra la dirección IP interna se termina la función
        if (founded)
        {
            break;
        }
    }
}

// Buscar nombre de computadora
void Bitacora::searchByMail()
{
    for (int j = 0; j < total_entries; j++)
    {
        // Si el nombre coincide
        if (nombre_destino[j] == "server.reto.com")
        {
            cout << "Si se encontro a: " << nombre_destino[j] << endl;
            break; // Sale del ciclo
        }
    }
}

// Encuentra e imprime todos los servicios de mensajería usados
void Bitacora::findAllMails()
{
    vector<string> emails;
    bool repeatedEmail = false;

    for (int i = 0; i < total_entries; i++)
    {
        // Si el nombre esta registrado correctamente
        if (nombre_destino[i] != "-")
        {
            // Para cada email registrado en el vector emails
            for (int j = 0; j < emails.size(); j++)
            {
                // Si el nombre del correo ya esta dentro del vector correo
                if (nombre_destino[i] == emails[j])
                {
                    repeatedEmail = true; // Marca que ese correo ya esta en el vector
                    break;                // Deja de comparar con los siguientes correos
                }
            }

            // Si al final de compara con todos los correos no estaba en la lista
            if (!repeatedEmail)
            {
                emails.push_back(nombre_destino[i]); // Añade el nuevo correo a la lista
            }

            repeatedEmail = false; // Regresa valor a falso para siguiente ciclo
        }
    }

    // Ordenamiento de vector emails
    int i, j;
    string index;

    // Para i < n y empezando en 1
    for (i = 1; i < emails.size(); i++)
    {
        // Index es el valor inicial del arreglo en i y j es el indice anterior a i
        index = emails[i];
        j = i - 1;

        // Mientras que i no haya llegado al inicio y el numero anterior sea mas grande que el inicial cambialos
        while (j >= 0 && emails[j] > index)
        {
            emails[j + 1] = emails[j];
            j--;
        }

        // Pon el valor inicial en su posicion correcta
        emails[j + 1] = index;
    }

    // Se imprimen los emails
    cout << endl;
    cout << "Direcciones de correo: " << endl;
    for (int k = 0; k < emails.size(); k++)
    {
        cout << "- " << emails[k] << endl;
    }
}

void Bitacora::PrintPorts()
{
    vector<int> smallPorts;  // Vector que contendra los puertos nuevos encontrados
    bool isRepeated = false; // Marcador que indica si ya esta dentro del vector
    int puerto;

    // Para cada registro
    for (int i = 0; i < total_entries; i++)
    {
        // Si el puerto valido
        if (puerto_destino[i] != "-")
        {
            // Si el puerto es menor a 1000
            if (stoi(puerto_destino[i]) < 1000)
            {
                // Para cada puerto en el vector de puertos encontrados debajo de 1000
                for (int j = 0; j < smallPorts.size(); j++)
                {
                    // Si ya está en el vector
                    if (stoi(puerto_destino[i]) == smallPorts[j])
                    {
                        isRepeated = true; // Marca que ya se repitio
                        break;             // Termina el ciclo
                    }
                }

                // Si no se ha repetido
                if (!isRepeated)
                {
                    smallPorts.push_back(stoi(puerto_destino[i])); // Agrega el nuevo puerto al vector
                }

                isRepeated = false; // Regresa valor a falso para siguiente iteración
            }
        }
    }

    // Ordenar el arreglo de menor a mayor con algoritmo de burbuja
    int i, j, index;

    // Para i < n y empezando en 1
    for (i = 1; i < smallPorts.size(); i++)
    {
        // Index es el valor inicial del arreglo en i y j es el indice anterior a i
        index = smallPorts[i];
        j = i - 1;

        // Mientras que i no haya llegado al inicio y el numero anterior sea mas grande que el inicial cambialos
        while (j >= 0 && smallPorts[j] > index)
        {
            smallPorts[j + 1] = smallPorts[j];
            j--;
        }

        // Pon el valor inicial en su posicion correcta
        smallPorts[j + 1] = index;
    }

    // Imprime los puertos encontrados
    cout << "Puertos menores a 1000:" << endl;
    for (int i = 0; i < smallPorts.size(); i++)
    {
        cout << "- " << smallPorts[i] << endl;
    }
}