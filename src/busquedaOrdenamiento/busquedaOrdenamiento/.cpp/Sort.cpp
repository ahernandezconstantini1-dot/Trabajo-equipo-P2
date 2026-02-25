#include "sort.h"
#include <iostream>
#include <vector>

using namespace std;

// 0/ Imprime el arreglo (usado en verbose)
static void imprimir(int arreglo[], int n)
{
    for (int i = 0; i < n; i++) cout << arreglo[i] << " ";
    cout << "\n";
}

void ordenarBurbuja(int arreglo[], int n, bool verbose)
{
    // 0/ Burbuja: compara vecinos e intercambia si están en orden incorrecto
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (verbose)
                cout << "[Burbuja] comparo a[" << j << "]=" << arreglo[j]
                     << " con a[" << (j + 1) << "]=" << arreglo[j + 1] << "\n";

            if (arreglo[j] > arreglo[j + 1])
            {
                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;

                if (verbose)
                {
                    cout << "  swap -> ";
                    imprimir(arreglo, n);
                }
            }
        }
    }
}

void ordenarSeleccion(int arreglo[], int n, bool verbose)
{
    // 0/ Selección: encuentra el mínimo del resto y lo pone en su posición
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (verbose)
                cout << "[Seleccion] comparo a[" << j << "]=" << arreglo[j]
                     << " con a[" << minIdx << "]=" << arreglo[minIdx] << "\n";

            if (arreglo[j] < arreglo[minIdx]) minIdx = j;
        }

        if (minIdx != i)
        {
            int temp = arreglo[i];
            arreglo[i] = arreglo[minIdx];
            arreglo[minIdx] = temp;

            if (verbose)
            {
                cout << "  swap i=" << i << " con minIdx=" << minIdx << " -> ";
                imprimir(arreglo, n);
            }
        }
    }
}

void ordenarInsercion(int arreglo[], int n, bool verbose)
{
    // 0/ Inserción: toma una "clave" y la inserta en la parte ordenada
    for (int i = 1; i < n; i++)
    {
        int clave = arreglo[i];
        int j = i - 1;

        if (verbose) cout << "[Insercion] clave=" << clave << "\n";

        while (j >= 0 && arreglo[j] > clave)
        {
            if (verbose)
                cout << "  muevo a[" << j << "]=" << arreglo[j] << " a posicion " << (j + 1) << "\n";

            arreglo[j + 1] = arreglo[j];
            j--;
        }

        arreglo[j + 1] = clave;

        if (verbose)
        {
            cout << "  inserto clave en " << (j + 1) << " -> ";
            imprimir(arreglo, n);
        }
    }
}

// 0/ QuickSort con indent para que se entienda la recursión
static void quickSortInterno(int arreglo[], int izquierda, int derecha,
                             int& comparaciones, int& intercambios,
                             bool verbose, int depth)
{
    int i = izquierda;
    int j = derecha;
    int pivote = arreglo[(izquierda + derecha) / 2];

    if (verbose)
    {
        for (int k = 0; k < depth; k++) cout << "  ";
        cout << "[Quick] rango " << izquierda << "-" << derecha << " pivote=" << pivote << "\n";
    }

    while (i <= j)
    {
        while (arreglo[i] < pivote) { i++; comparaciones++; }
        while (arreglo[j] > pivote) { j--; comparaciones++; }

        if (i <= j)
        {
            int temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
            intercambios++;

            if (verbose)
            {
                for (int k = 0; k < depth; k++) cout << "  ";
                cout << "  swap i=" << i << " j=" << j << "\n";
            }

            i++;
            j--;
        }
    }

    if (izquierda < j) quickSortInterno(arreglo, izquierda, j, comparaciones, intercambios, verbose, depth + 1);
    if (i < derecha)   quickSortInterno(arreglo, i, derecha, comparaciones, intercambios, verbose, depth + 1);
}

void quickSort(int arreglo[], int izquierda, int derecha, int& comparaciones, int& intercambios, bool verbose)
{
    // 0/ Wrapper para iniciar quicksort con profundidad 0
    quickSortInterno(arreglo, izquierda, derecha, comparaciones, intercambios, verbose, 0);
}

// 0/ Merge seguro (sin temp[100]) + verbose
static void merge(int arreglo[], int izquierda, int medio, int derecha, int& comparaciones, bool verbose)
{
    int i = izquierda;
    int j = medio + 1;

    vector<int> temp;
    temp.reserve((derecha - izquierda + 1));

    if (verbose)
        cout << "[Merge] combino " << izquierda << "-" << medio << " con " << (medio + 1) << "-" << derecha << "\n";

    while (i <= medio && j <= derecha)
    {
        comparaciones++;
        if (arreglo[i] <= arreglo[j]) temp.push_back(arreglo[i++]);
        else                          temp.push_back(arreglo[j++]);
    }

    while (i <= medio) temp.push_back(arreglo[i++]);
    while (j <= derecha) temp.push_back(arreglo[j++]);

    for (int k = 0; k < (int)temp.size(); k++)
        arreglo[izquierda + k] = temp[k];
}

static void mergeSortInterno(int arreglo[], int izquierda, int derecha, int& comparaciones, bool verbose, int depth)
{
    if (izquierda >= derecha) return;

    int medio = (izquierda + derecha) / 2;

    if (verbose)
    {
        for (int k = 0; k < depth; k++) cout << "  ";
        cout << "[MergeSort] divido " << izquierda << "-" << derecha << " -> "
             << izquierda << "-" << medio << " y " << (medio + 1) << "-" << derecha << "\n";
    }

    mergeSortInterno(arreglo, izquierda, medio, comparaciones, verbose, depth + 1);
    mergeSortInterno(arreglo, medio + 1, derecha, comparaciones, verbose, depth + 1);
    merge(arreglo, izquierda, medio, derecha, comparaciones, verbose);
}

void mergeSort(int arreglo[], int izquierda, int derecha, int& comparaciones, bool verbose)
{
    // 0/ Wrapper para iniciar mergeSort con profundidad 0
    mergeSortInterno(arreglo, izquierda, derecha, comparaciones, verbose, 0);
}