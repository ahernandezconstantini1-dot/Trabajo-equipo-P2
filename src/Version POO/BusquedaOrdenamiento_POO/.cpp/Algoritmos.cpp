/**
 * @file Algoritmos.cpp
 * @brief Implementación de los métodos de ordenamiento y búsqueda de la clase Algoritmos.
 * @details Este archivo consolida las funciones de procesamiento de datos desarrolladas
 * originalmente en Sort.cpp y search.cpp, adaptadas a un entorno POO estático.
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#include "Algoritmos.h"
#include <iostream>
#include <vector>

using namespace std;

// --- MÉTODOS DE ORDENAMIENTO (Basados en Sort.cpp) ---

/**
 * @brief Algoritmo de Ordenamiento Burbuja.
 * @details Compara pares de elementos adyacentes y los intercambia si están en el orden incorrecto.
 * @note Complejidad temporal: $O(n^2)$.
 * @param arreglo Puntero al arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @param verbose Si es true, imprime cada intercambio en consola.
 */
void Algoritmos::burbuja(int arreglo[], int n, bool verbose) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
                if (verbose) cout << "[Burbuja] Swap: " << arreglo[j] << " <-> " << arreglo[j + 1] << "\n";
            }
        }
    }
}

/**
 * @brief Algoritmo de Ordenamiento por Selección.
 * @details Busca el elemento mínimo y lo coloca al principio del arreglo de forma iterativa.
 * @note Complejidad temporal: $O(n^2)$.
 * @param arreglo Puntero al arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @param verbose Si es true, imprime los índices del intercambio.
 */
void Algoritmos::seleccion(int arreglo[], int n, bool verbose) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arreglo[j] < arreglo[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(arreglo[i], arreglo[minIdx]);
            if (verbose) cout << "[Seleccion] Swap i=" << i << " con minIdx=" << minIdx << "\n";
        }
    }
}

/**
 * @brief Algoritmo de Ordenamiento por Inserción.
 * @details Construye el arreglo ordenado de uno en uno, insertando cada elemento en su posición correcta.
 * @note Complejidad temporal: $O(n^2)$.
 * @param arreglo Puntero al arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @param verbose Si es true, imprime la clave insertada.
 */
void Algoritmos::insercion(int arreglo[], int n, bool verbose) {
    for (int i = 1; i < n; i++) {
        int clave = arreglo[i];
        int j = i - 1;
        while (j >= 0 && arreglo[j] > clave) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = clave;
        if (verbose) cout << "[Insercion] Clave " << clave << " insertada.\n";
    }
}

/**
 * @brief Algoritmo de Ordenamiento QuickSort.
 * @details Utiliza la técnica de "divide y vencerás" mediante un pivote para particionar el arreglo.
 * @note Complejidad temporal promedio: $O(n \log n)$.
 * @param arreglo Puntero al arreglo de enteros.
 * @param izquierda Índice inicial del subarreglo.
 * @param derecha Índice final del subarreglo.
 * @param comparaciones Contador de comparaciones realizadas (paso por referencia).
 * @param intercambios Contador de intercambios realizados (paso por referencia).
 * @param verbose Si es true, muestra el flujo del algoritmo.
 */
void Algoritmos::quick(int arreglo[], int izquierda, int derecha, int& comparaciones, int& intercambios, bool verbose) {
    int i = izquierda, j = derecha;
    int pivote = arreglo[(izquierda + derecha) / 2];
    while (i <= j) {
        while (arreglo[i] < pivote) { i++; comparaciones++; }
        while (arreglo[j] > pivote) { j--; comparaciones++; }
        if (i <= j) {
            swap(arreglo[i], arreglo[j]);
            intercambios++; i++; j--;
        }
    }
    if (izquierda < j) quick(arreglo, izquierda, j, comparaciones, intercambios, verbose);
    if (i < derecha) quick(arreglo, i, derecha, comparaciones, intercambios, verbose);
}

/**
 * @brief Algoritmo de Ordenamiento MergeSort.
 * @details Divide el arreglo en mitades recursivamente y las combina de forma ordenada.
 * @note Complejidad temporal: $O(n \log n)$.
 * @param arreglo Puntero al arreglo de enteros.
 * @param izquierda Índice inicial.
 * @param derecha Índice final.
 * @param comparaciones Contador de comparaciones.
 * @param verbose Si es true, muestra el estado de la unión.
 */
void Algoritmos::merge(int arreglo[], int izquierda, int derecha, int& comparaciones, bool verbose) {
    if (izquierda >= derecha) return;
    int medio = (izquierda + derecha) / 2;
    merge(arreglo, izquierda, medio, comparaciones, verbose);
    merge(arreglo, medio + 1, derecha, comparaciones, verbose);

    vector<int> temp;
    int i = izquierda, j = medio + 1;
    while (i <= medio && j <= derecha) {
        comparaciones++;
        if (arreglo[i] <= arreglo[j]) temp.push_back(arreglo[i++]);
        else temp.push_back(arreglo[j++]);
    }
    while (i <= medio) temp.push_back(arreglo[i++]);
    while (j <= derecha) temp.push_back(arreglo[j++]);
    for (int k = 0; k < temp.size(); k++) arreglo[izquierda + k] = temp[k];
}

// --- MÉTODOS DE BÚSQUEDA (Basados en search.cpp) ---

/**
 * @brief Realiza una búsqueda secuencial en el arreglo.
 * @details Recorre cada elemento hasta encontrar el valor buscado.
 * @note Complejidad temporal: $O(n)$.
 * @param arreglo Puntero al arreglo.
 * @param n Tamaño.
 * @param valor El número a buscar.
 * @param verbose Si es true, imprime cada comparación.
 * @return Índice del elemento encontrado o -1 si no existe.
 */
int Algoritmos::secuencial(int arreglo[], int n, int valor, bool verbose) {
    for (int i = 0; i < n; i++) {
        if (verbose) cout << "[Secuencial] i=" << i << " comparo " << arreglo[i] << " con " << valor << "\n";
        if (arreglo[i] == valor) return i;
    }
    return -1;
}

/**
 * @brief Realiza una búsqueda binaria.
 * @details Divide el rango de búsqueda a la mitad en cada paso.
 * @attention Requiere que el arreglo esté previamente ordenado.
 * @note Complejidad temporal: $O(\log n)$.
 * @param arreglo Puntero al arreglo ordenado.
 * @param n Tamaño.
 * @param valor El número a buscar.
 * @param verbose Si es true, muestra el punto medio calculado.
 * @return Índice del elemento o -1 si no existe.
 */
int Algoritmos::binaria(int arreglo[], int n, int valor, bool verbose) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (verbose) cout << "[Binaria] medio=" << medio << " val=" << arreglo[medio] << "\n";
        if (arreglo[medio] == valor) return medio;
        if (arreglo[medio] < valor) izq = medio + 1;
        else der = medio - 1;
    }
    return -1;
}