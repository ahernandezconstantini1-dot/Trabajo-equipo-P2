/**
 * @file Algoritmos.h
 * @brief Declaración de la clase Algoritmos y sus métodos de procesamiento.
 * @details Esta librería estática centraliza los algoritmos de ordenamiento
 * y búsqueda para facilitar su llamada desde el AnalizadorDeRendimiento.
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#pragma once
#ifndef ALGORITMOS_H
#define ALGORITMOS_H

 /**
  * @class Algoritmos
  * @brief Contiene las implementaciones estáticas de los algoritmos de ordenamiento y búsqueda.
  * @details Todos los métodos son estáticos para permitir su uso sin instanciar la clase,
  * facilitando la medición de tiempos mediante lambdas.
  */
class Algoritmos {
public:
    // --- MÉTODOS DE ORDENAMIENTO ---

    /**
     * @brief Ordena un arreglo mediante el método de Burbuja.
     * @note Complejidad: $O(n^2)$.
     * @param arr Puntero al arreglo de enteros.
     * @param n Tamaño del arreglo.
     * @param verbose Indica si se debe imprimir el proceso paso a paso.
     */
    static void burbuja(int arr[], int n, bool verbose);

    /**
     * @brief Ordena un arreglo mediante el método de Selección.
     * @note Complejidad: $O(n^2)$.
     * @param arr Puntero al arreglo.
     * @param n Tamaño del arreglo.
     * @param verbose Modo detallado.
     */
    static void seleccion(int arr[], int n, bool verbose);

    /**
     * @brief Ordena un arreglo mediante el método de Inserción.
     * @note Complejidad: $O(n^2)$.
     * @param arr Puntero al arreglo.
     * @param n Tamaño del arreglo.
     * @param verbose Modo detallado.
     */
    static void insercion(int arr[], int n, bool verbose);

    /**
     * @brief Ordena un arreglo utilizando el algoritmo QuickSort.
     * @note Complejidad promedio: $O(n \log n)$.
     * @param arr Puntero al arreglo.
     * @param izq Índice inicial.
     * @param der Índice final.
     * @param comp Referencia al contador de comparaciones.
     * @param inter Referencia al contador de intercambios.
     * @param verbose Modo detallado.
     */
    static void quick(int arr[], int izq, int der, int& comp, int& inter, bool verbose);

    /**
     * @brief Ordena un arreglo utilizando el algoritmo MergeSort.
     * @note Complejidad: $O(n \log n)$.
     * @param arr Puntero al arreglo.
     * @param izq Índice inicial.
     * @param der Índice final.
     * @param comp Referencia al contador de comparaciones.
     * @param verbose Modo detallado.
     */
    static void merge(int arr[], int izq, int der, int& comp, bool verbose);

    // --- MÉTODOS DE BÚSQUEDA ---

    /**
     * @brief Realiza una búsqueda secuencial de un valor.
     * @note Complejidad: $O(n)$.
     * @param arr Puntero al arreglo.
     * @param n Tamaño del arreglo.
     * @param valor Número a buscar.
     * @param verbose Modo detallado.
     * @return El índice del valor o -1 si no se encuentra.
     */
    static int secuencial(int arr[], int n, int valor, bool verbose);

    /**
     * @brief Realiza una búsqueda binaria de un valor.
     * @attention Requiere que el arreglo esté ordenado.
     * @note Complejidad: $O(\log n)$.
     * @param arr Puntero al arreglo ordenado.
     * @param n Tamaño del arreglo.
     * @param valor Número a buscar.
     * @param verbose Modo detallado.
     * @return El índice del valor o -1 si no se encuentra.
     */
    static int binaria(int arr[], int n, int valor, bool verbose);
};

#endif