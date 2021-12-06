#include <iostream>
#include <vector>
#include "bitacora.hpp"

// El constructor recibe el nombre der archivo y carga los datos a los vectores
Bitacora::Bitacora(string _file_name)
{
    file_name = _file_name;
    LoadData();
}

// Imprime la informacion de los vectores
void Bitacora::print()
{
    for (int i = 0; i < 30; i++)
    {
        cout << entries[i].fecha << " | " << entries[i].hora <<
        " | " << entries[i].ip_origen << 
        " | " << entries[i].puerto_origen << 
        " | " << entries[i].nombre_origen << 
        " | " << entries[i].ip_destino << 
        " | " << entries[i].puerto_destino <<
        " | " << entries[i].nombre_destino << endl;
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

        string fecha = column_data[0];
        string hora = column_data[1];
        string ip_origen = column_data[2];
        string puerto_origen = column_data[3];
        string nombre_origen = column_data[4];
        string ip_destino = column_data[5];
        string puerto_destino= column_data[6];
        string nombre_destino= column_data[7];

        Entry currentEntry(fecha,hora,ip_origen,puerto_origen,nombre_origen,ip_destino
        ,puerto_destino,nombre_destino);

        entries.push_back(currentEntry);
    }

    total_entries = entries.size();
}

vector<Entry> Bitacora::getEntries(){
    return entries;
}

