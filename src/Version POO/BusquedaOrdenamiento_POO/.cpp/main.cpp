/**
 * @file main.cpp
 * @brief Punto de entrada principal para el sistema de análisis de algoritmos.
 * @details Este archivo implementa un menú interactivo que coordina las clases
 * ArregloManager, Algoritmos y AnalizadorDeRendimiento. Permite al usuario
 * evaluar el rendimiento de búsquedas y ordenamientos en tiempo real.
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#include <iostream>
#include <vector>
#include <string>
#include "ArregloManager.h"
#include "Algoritmos.h"
#include "AnalizadorDeRendimiento.h"

using namespace std;

/**
 * @brief Función principal (Entry point).
 * @details Gestiona el flujo del programa, la toma de decisiones del usuario a través
 * de la consola y la invocación de las herramientas de medición de rendimiento.
 * @return int Estado de salida del programa (0 para éxito).
 */
int main() {
    /** @brief Instancia del gestor de datos para manejar el ciclo de vida del arreglo. */
    ArregloManager gestor;

    int opcion, subOpcion, valorBusqueda, pos;
    bool verbose = false; /**< Controla si se imprimen los pasos intermedios de los algoritmos. */

    // Inicialización del arreglo
    gestor.generarInteractivo();

    do {
        cout << "\n=== MENU PRINCIPAL (POO) ===\n";
        cout << "0. Generar nuevo arreglo\n1. Busqueda Secuencial\n2. Busqueda Binaria\n3. Ordenamiento\n4. Salir\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
        case 0:
            /** @section Caso_0 Generación de Datos
             * Permite reconfigurar el arreglo y activar el modo paso a paso (verbose).
             */
            gestor.generarInteractivo();
            cout << "Activar modo proceso paso a paso? (1=Si, 0=No): ";
            cin >> verbose;
            break;

        case 1:
            /** @section Caso_1 Búsqueda Secuencial
             * Realiza la búsqueda y mide el tiempo de respuesta.
             */
            valorBusqueda = 10; // Ejemplo o pedir al usuario
            cout << "Buscando valor " << valorBusqueda << "...\n";

            // Diego mide el tiempo de búsqueda secuencial usando lambdas
            {
                double t = AnalizadorDeRendimiento::medir([&]() {
                    pos = Algoritmos::secuencial(gestor.getRawData(), gestor.getTamano(), valorBusqueda, verbose);
                    });
                cout << "Resultado: " << (pos != -1 ? "Encontrado en " + to_string(pos) : "No encontrado") << "\n";
                cout << "Tiempo de ejecucion: " << t << " ms\n";
            }
            break;

        case 3:
            /** @section Caso_3 Ordenamiento
             * Permite elegir entre algoritmos cuadráticos $O(n^2)$ y logarítmicos $O(n \log n)$.
             */
            cout << "\n1. Burbuja\n2. QuickSort\nElija metodo: ";
            cin >> subOpcion;

            if (subOpcion == 1) {
                // Medición del tiempo para Burbuja O(n^2)
                double t = AnalizadorDeRendimiento::medir([&]() {
                    Algoritmos::burbuja(gestor.getRawData(), gestor.getTamano(), verbose);
                    });
                cout << "Ordenamiento Burbuja completado en: " << t << " ms\n";
            }
            else {
                int comp = 0, inter = 0;
                // Medición del tiempo para QuickSort O(n log n)
                double t = AnalizadorDeRendimiento::medir([&]() {
                    Algoritmos::quick(gestor.getRawData(), 0, gestor.getTamano() - 1, comp, inter, verbose);
                    });
                cout << "QuickSort completado en: " << t << " ms\n";
            }
            gestor.mostrar(); //
            break;
        }
    } while (opcion != 4);

    return 0;
}