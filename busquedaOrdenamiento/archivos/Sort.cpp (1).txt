#include "sort.h"
#include <vector>

void ordenarBurbuja(int arreglo[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (arreglo[j] > arreglo[j + 1])
            {
                temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

void ordenarSeleccion(int arreglo[], int n)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (arreglo[j] < arreglo[min])
            {
                min = j;
            }
        }

        temp = arreglo[i];
        arreglo[i] = arreglo[min];
        arreglo[min] = temp;
    }
}

void ordenarInsercion(int arreglo[], int n)
{
    int i, j, clave;

    for (i = 1; i < n; i++)
    {
        clave = arreglo[i];
        j = i - 1;

        while (j >= 0 && arreglo[j] > clave)
        {
            arreglo[j + 1] = arreglo[j];
            j--;
        }

        arreglo[j + 1] = clave;
    }
}

void quickSort(int arreglo[], int izquierda, int derecha, int& comparaciones, int& intercambios)
{
    int i = izquierda;
    int j = derecha;
    int pivote = arreglo[(izquierda + derecha) / 2];
    int temp;

    while (i <= j)
    {
        while (arreglo[i] < pivote)
        {
            i++;
            comparaciones++;
        }

        while (arreglo[j] > pivote)
        {
            j--;
            comparaciones++;
        }

        if (i <= j)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
            intercambios++;

            i++;
            j--;
        }
    }

    if (izquierda < j)
        quickSort(arreglo, izquierda, j, comparaciones, intercambios);

    if (i < derecha)
        quickSort(arreglo, i, derecha, comparaciones, intercambios);
}

void merge(int arreglo[], int izquierda, int medio, int derecha, int& comparaciones)
{
    int i = izquierda;
    int j = medio + 1;
    int k = 0;

    std::vector<int> temp(derecha - izquierda + 1);

    while (i <= medio && j <= derecha)
    {
        comparaciones++;

        if (arreglo[i] <= arreglo[j])
            temp[k++] = arreglo[i++];
        else
            temp[k++] = arreglo[j++];
    }

    while (i <= medio)  temp[k++] = arreglo[i++];
    while (j <= derecha) temp[k++] = arreglo[j++];

    for (i = izquierda, k = 0; i <= derecha; i++, k++)
        arreglo[i] = temp[k];
}

void mergeSort(int arreglo[], int izquierda, int derecha, int& comparaciones)
{
    int medio;

    if (izquierda < derecha)
    {
        medio = (izquierda + derecha) / 2;

        mergeSort(arreglo, izquierda, medio, comparaciones);
        mergeSort(arreglo, medio + 1, derecha, comparaciones);
        merge(arreglo, izquierda, medio, derecha, comparaciones);
    }
}
