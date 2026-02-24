#include "search.h"

int busquedaSecuencial(int arreglo[], int n, int valor)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (arreglo[i] == valor)
        {
            return i;  // devuelve posición
        }
    }

    return -1; // no encontrado
}

int busquedaBinaria(int arreglo[], int n, int valor)
{
    int izquierda = 0;
    int derecha = n - 1;
    int medio;

    while (izquierda <= derecha)
    {
        medio = (izquierda + derecha) / 2;

        if (arreglo[medio] == valor)
        {
            return medio;
        }
        else if (arreglo[medio] < valor)
        {
            izquierda = medio + 1;
        }
        else
        {
            derecha = medio - 1;
        }
    }

    return -1;
}