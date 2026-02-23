#include <iostream>
#include <vector>
#include "randomgen.h"
#include "view.h"
#include "sort.h"
#include "search.h"
using namespace std;

int main()
{
    // Inicializaciones: O(1)
    vector<int> arregloVec;
    int n = 0;
    bool verbose = false;
    int comparaciones = 0, intercambios = 0;

    // Generar arreglo inicial: O(n) o O(rango)
    arregloVec = generarArregloInteractivo(n);  // → O(n)

    int opcion = 0;

    // Declarar la variable 'valor' antes de usarla en el switch
    int valor = 0;

    // Declarar la variable 'posicion' antes de usarla en el switch
    int posicion = -1;

    // Declarar la variable 'metodo' antes de usarla en el switch
    int metodo = 0;

    do {
        mostrarMenu();           // O(1)
        cin >> opcion;           // O(1)

        switch (opcion) {
        case 0:  // Regenerar
            arregloVec = generarArregloInteractivo(n);  // O(n)
            break;

        case 1:
            // O(n) - Recorre todo el arreglo para mostrarlo
            mostrarArreglo(arregloVec.data(), n);

            // O(1) - Entrada de usuario constante
            valor = pedirValor();

            // O(n) - Búsqueda secuencial con verbose opcional
            // Peor caso: recorre todo el arreglo (valor no existe o está al final)
            // Mejor caso: O(1) si el valor está en la primera posición
            posicion = busquedaSecuencial(arregloVec.data(), n, valor, verbose);

            // O(1) - Impresión de resultado
            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 2:
            // O(1) - Impresión de mensaje inicial
            cout << "\nOrdenando arreglo con burbuja...\n";

            // O(n²) - Ordenamiento Burbuja (peor y mejor caso siempre n²)
            // Comparaciones: (n-1) + (n-2) + ... + 1 = n(n-1)/2 ≈ n²/2
            // Intercambios: 0 hasta n²/2 dependiendo de desorden
            ordenarBurbuja(arregloVec.data(), n, verbose);

            // O(n) - Recorre todo el arreglo ordenado para mostrarlo
            mostrarArreglo(arregloVec.data(), n);

            // O(1) - Entrada de usuario constante
            valor = pedirValor();

            // O(log n) - Búsqueda binaria (divide y conquista)
            // Peor caso: log₂(n) + 1 comparaciones
            // Mejor caso: 1 comparación (elemento en medio)
            posicion = busquedaBinaria(arregloVec.data(), n, valor, verbose);

            // O(1) - Impresión de resultado
            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 3:
            // O(1) - Mostrar menú y leer opción del usuario
            metodo = mostrarMenuOrdenamiento();

            // O(1) - Reinicio de contadores para métricas
            comparaciones = 0;
            intercambios = 0;

            // Selección de método de ordenamiento
            // Cada método tiene diferente complejidad temporal
            if (metodo == 1)
            {
                // O(n²) - Burbuja: siempre cuadrático
                ordenarBurbuja(arregloVec.data(), n, verbose);
            }
            else if (metodo == 2)
            {
                // O(n²) - Selección: siempre cuadrático (n-1 pasadas)
                ordenarSeleccion(arregloVec.data(), n, verbose);
            }
            else if (metodo == 3)
            {
                // O(n²) peor caso, O(n) mejor caso (arreglo ordenado)
                ordenarInsercion(arregloVec.data(), n, verbose);
            }
            else if (metodo == 4)
            {
                // O(n log n) promedio, O(n²) peor caso (pivotes malos)
                // Complejidad depende de la aleatoriedad del pivote
                quickSort(arregloVec.data(), 0, n - 1, comparaciones, intercambios, verbose);
                cout << "Comparaciones: " << comparaciones << endl;
                cout << "Intercambios: " << intercambios << endl;
            }
            else if (metodo == 5)
            {
                // O(n log n) garantizado - divide siempre a la mitad
                mergeSort(arregloVec.data(), 0, n - 1, comparaciones, verbose);
                cout << "Comparaciones: " << comparaciones << endl;
            }
            else
            {
                // O(1) - Manejo de error
                cout << "Metodo invalido.\n";
            }

            // O(n) - Mostrar resultado del ordenamiento
            cout << "\nArreglo ordenado:\n";
            mostrarArreglo(arregloVec.data(), n);
            break;
        case 4:  // Salir
            break;
        }
    } while (opcion != 4);  // Itera k veces (k = número de operaciones del usuario)
}