#include <iostream>
#include "assets/ConexionesComputadora.cpp"
#include "assets/bitacora.cpp"

using namespace std;

int main()
{
    // Se crea objeto de clase ConexionesComputadora
    Bitacora entries("equipo1.csv");
    ConexionesComputadora conexion = ConexionesComputadora(entries.getEntries());

    int opcion = -1;
    while (opcion != 0)
    {
        // Menu
        cout << endl;
        cout << "--- MENU ---" << endl;
        cout << "1) Ver direccion de ip de equipo: " << endl;
        cout << "2) Ver nombre de equipo: " << endl;
        cout << "3) Ver conexiones entrantes " << endl;
        cout << "4) Ver conexiones salientes" << endl;
        cout << "5) Ver la ultima conexion entrante" << endl;
        cout << "6) Ver longitud conexiones entrantes" << endl;
        cout << "7) Ver longitud conexiones salientes" << endl;
        cout << "8) Verificar 3 conexiones seguidas a sitio web" << endl;
        cout << "0) Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        // Pregunta 1
        case 1:
            cout << endl;
            cout << "Direccion IP de equipo: " << conexion.ip << endl;
            break;

        // Pregunta 2 - LISTO
        case 2:
            cout << endl;
            cout << "El nombre es: " << conexion.nombre << endl;
            break;

        // Pregunta 3
        case 3:
            conexion.imprimir_ConexionesEntrantes();
            break;

        // Pregunta 4
        case 4:
            conexion.imprimir_ConexionesSalientes();
            break;

        // Pregunta 5
        case 5:
            conexion.ultimaConexionEntrante();
            break;

        // Pregunta 6
        case 6:
            conexion.longitudEntrantes();
            break;

        // Pregunta 7
        case 7:
            conexion.longitudSalientes();
            break;

        // Pregunta 8
        case 8:
            conexion.conexionesSeguidas();
            break;
        }
    }

    return 0;
}
