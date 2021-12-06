#include <iostream>
#include <string>
#include "bitacora.cpp"
using namespace std;

int main()
{
    Bitacora entries("equipo1.csv");
    string nombres[7] = {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    int opcion;

    while (opcion != 0)
    {
        // Menu
        cout << endl;
        cout << "--- MENU ---" << endl;
        cout << "1) Cuantos registros tiene tu archivo?: " << endl;
        cout << "2) Cuantos records hay del segundo dia registrado? Que dia es este?: " << endl;
        cout << "3) Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond? A quienes?: " << endl;
        cout << "4) Cual es la direccion de la red interna de la compania?: " << endl;
        cout << "5) Alguna computadora se llama server.reto.com?: " << endl;
        cout << "6) Que servicio de correo electronico utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)?: " << endl;
        cout << "7) Considerando solamente los puertos destino Que puertos abajo del 1000 se estan usando?:" << endl;
        cout << "0) Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        // Pregunta 1
        case 1:
            cout << endl;
            cout << "Registros de Archivo: " << entries.total_entries << endl;
            break;

        // Pregunta 2
        case 2:
            cout << endl;
            entries.countRegistersInADay(2);
            break;

        // Pregunta 3
        case 3:
            cout << endl;
            entries.searchByName(nombres, 7);
            break;

        // Pregunta 4
        case 4:
            entries.SearchInternalIp();
            break;

        // Pregunta 5
        case 5:
            cout << endl;
            entries.searchByMail();
            break;

        // Pregunta 6
        case 6:
            entries.findAllMails();
            break;

        // Pregunta 7
        case 7:
            entries.PrintPorts();
            break;
        }
    }

    return 0;
}