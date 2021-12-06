#include <iostream>
#include "assets/ConexionesComputadora.cpp"
#include "assets/bitacora.cpp"
#include "assets/TreeNode.hpp"
#include "assets/BinaryTree.hpp"
#include "assets/BST.hpp"

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
        cout << "1) Existe algun sitio que se mantenga en el top 5 todos los dias?" << endl;
        cout << "2) Existe algun sitio que entre al top 5 a partir de un dia y de ahi aparezca en todos los dias subsecuentes?" << endl;
        cout << "3) Existe algun sitio que aparezca en el top 5 con una cantidad mas alta de trafico que lo normal?" << endl;
        cout << "0) Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        // Pregunta 1
        case 1:
            conexion.top5TodosLosDias();
            break;

        // Pregunta 2
        case 2:
            conexion.top5APartirDeUnDia();
            break;

        // Pregunta 3
        case 3:
            conexion.conexionMasAltaNormal();
            break;
        }
    }

    return 0;
}