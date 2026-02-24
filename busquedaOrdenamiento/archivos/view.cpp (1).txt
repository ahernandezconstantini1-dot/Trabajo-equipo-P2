#include <iostream>
using namespace std;
#include "view.h"

void mostrarMenu()
{
    cout << "\n=== MENU ===\n";
    cout << "1. Busqueda Secuencial\n";
    cout << "2. Busqueda Binaria (ordena automaticamente)\n";
    cout << "3. Ordenar Arreglo\n";
    cout << "4. Benchmarks (medir tiempos)\n";
    cout << "5. Salir\n";
    cout << "Seleccione opcion: ";
}

void mostrarArreglo(int arreglo[], int n)
{
    int i;

    cout << "\nArreglo: ";
    for (i = 0; i < n; i++)
    {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

int pedirValor()
{
    int valor;
    cout << "Ingrese valor a buscar: ";
    cin >> valor;
    return valor;
}

int mostrarMenuOrdenamiento()
{
    int opcion;

    cout << "\n=== METODOS DE ORDENAMIENTO ===\n";
    cout << "1. Burbuja\n";
    cout << "2. Seleccion\n";
    cout << "3. Insercion\n";
    cout << "4. QuickSort\n";
    cout << "5. MergeSort\n";
    cout << "Seleccione metodo: ";
    cin >> opcion;

    return opcion;
}