#include "search.h"
#include <iostream>

using namespace std;

int busquedaSecuencial(int arreglo[], int n, int valor, bool verbose)
{
    // 0/ Recorre todo el arreglo comparando elemento por elemento
    for (int i = 0; i < n; i++)
    {
        if (verbose)
            cout << "[Secuencial] i=" << i << " comparo " << arreglo[i] << " con " << valor << "\n";

        if (arreglo[i] == valor)
            return i; // 0/ encontrado
    }

    return -1; // 0/ no encontrado
}

int busquedaBinaria(int arreglo[], int n, int valor, bool verbose)
{
    // 0/ Busca dividiendo el rango (requiere arreglo ordenado)
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha)
    {
        int medio = (izquierda + derecha) / 2;

        if (verbose)
            cout << "[Binaria] izq=" << izquierda << " der=" << derecha
                 << " medio=" << medio << " valMedio=" << arreglo[medio] << "\n";

        if (arreglo[medio] == valor) return medio;
        else if (arreglo[medio] < valor) izquierda = medio + 1;
        else derecha = medio - 1;
    }

    return -1;
}