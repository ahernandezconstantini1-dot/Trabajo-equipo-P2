/**
 * @file ArregloManager.cpp
 * @brief Implementación de la lógica de gestión y generación de arreglos.
 * @details Contiene los métodos para la validación de entradas de usuario y
 * algoritmos de generación aleatoria (con y sin repetición).
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#include "ArregloManager.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

/**
 * @brief Constructor por defecto.
 * @details Inicializa el tamaño del arreglo en cero.
 */
ArregloManager::ArregloManager() : n(0) {}

/**
 * @brief Realiza una lectura robusta de enteros desde la consola.
 * @param prompt El mensaje de instrucción para el usuario.
 * @param minPermitido El límite inferior aceptado para el valor.
 * @return Un entero validado mayor o igual al mínimo.
 */
int ArregloManager::leerEnteroSeguro(const string& prompt, int minPermitido) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= minPermitido) return x;
        cout << "Entrada invalida. Debe ser >= " << minPermitido << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * @brief Valida que la entrada del usuario se encuentre dentro de un rango numérico.
 * @param prompt Mensaje de instrucción.
 * @param minV Límite inferior (inclusive).
 * @param maxV Límite superior (inclusive).
 * @return Entero dentro del rango $[minV, maxV]$.
 */
int ArregloManager::leerEnteroRango(const string& prompt, int minV, int maxV) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= minV && x <= maxV) return x;
        cout << "Entrada invalida. Rango [" << minV << ", " << maxV << "].\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * @brief Menú interactivo para configurar y generar el arreglo de datos.
 * @details El método permite seleccionar tres tipos de dimensiones:
 * 1. $N$ lineal.
 * 2. $N \times N$ (cuadrático).
 * 3. $N \times M$ (rectangular).
 * * Implementa dos modos de generación:
 * - **Repetidos:** Usa `std::uniform_int_distribution` para llenar el vector.
 * - **Sin Repetidos:** Crea un "pool" de valores, aplica un `std::shuffle` y hace un `resize` al tamaño deseado.
 */
void ArregloManager::generarInteractivo() {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    cout << "\n=== GENERADOR DE ARREGLOS (VERSION POO) ===\n";
    cout << "1) N\n2) N*N\n3) N*M\n";
    int tipo = leerEnteroRango("Elige tipo (1-3): ", 1, 3);
    int N = leerEnteroSeguro("Ingresa N: ", 1);
    int M = (tipo == 3) ? leerEnteroSeguro("Ingresa M: ", 1) : 1;

    // Cálculo de tamaño del arreglo
    size_t size = (tipo == 1) ? (size_t)N : (tipo == 2) ? (size_t)N * N : (size_t)N * M;

    /** @note Límite de seguridad para evitar desbordamientos de memoria. */
    if (size > 5000000) size = 5000000;

    cout << "\n1) Permitir repetidos\n2) NO permitir repetidos\n";
    int modo = leerEnteroRango("Elige modo: ", 1, 2);

    int minVal = leerEnteroSeguro("Rango Min: ", -1000000);
    int maxVal = leerEnteroSeguro("Rango Max: ", minVal);

    if (modo == 1) {
        // Generación con repetición
        uniform_int_distribution<int> dist(minVal, maxVal);
        datos.assign(size, 0);
        for (auto& x : datos) x = dist(rng);
    }
    else {
        // Generación sin repetición mediante barajado (Shuffle)
        if ((long long)maxVal - minVal + 1 < (long long)size) maxVal = minVal + (int)size - 1;
        datos.clear();
        for (int i = minVal; i <= maxVal; ++i) datos.push_back(i);
        shuffle(datos.begin(), datos.end(), rng);
        datos.resize(size);
    }
    this->n = (int)size;
    cout << "Arreglo generado con exito. Tamano: " << n << "\n";
}

/**
 * @brief Imprime los elementos del arreglo en la salida estándar.
 * @details Por motivos de rendimiento y legibilidad, si el arreglo es mayor a 50 elementos,
 * solo se muestran los primeros 50 y se indica que el resto ha sido truncado.
 */
void ArregloManager::mostrar() const {
    cout << "\nArreglo: ";
    for (int i = 0; i < n && i < 50; i++) cout << datos[i] << " ";
    if (n > 50) cout << "... (truncado por espacio)";
    cout << endl;
}