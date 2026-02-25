/**
 * @file AnalizadorDeRendimiento.h
 * @brief Herramienta utilitaria para la medición de tiempos de ejecución.
 * @details Provee una interfaz estática para cronometrar cualquier bloque de código
 * utilizando relojes de alta resolución de la librería <chrono>.
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#pragma once
#include <chrono>
#include <functional>
#include <iostream>

 /**
  * @class AnalizadorDeRendimiento
  * @brief Clase para medir tiempos de ejecución de algoritmos.
  * @details Esta clase utiliza el patrón de diseño utilitario (métodos estáticos)
  * para facilitar la medición de rendimiento sin necesidad de instanciar objetos.
  */
class AnalizadorDeRendimiento {
public:
    /**
     * @brief Mide el tiempo de ejecución de una función lambda o puntero a función.
     * @details Captura el tiempo inicial y final usando high_resolution_clock y
     * calcula la diferencia en milisegundos.
     * @param func La función o bloque de código (lambda) que se desea evaluar.
     * @return Tiempo transcurrido en milisegundos ($ms$) como un valor de punto flotante.
     */
    static double medir(std::function<void()> func) {
        // Marca de tiempo inicial
        auto inicio = std::chrono::high_resolution_clock::now();

        // Ejecución de la lógica del algoritmo
        func();

        // Marca de tiempo final
        auto fin = std::chrono::high_resolution_clock::now();

        // Cálculo de la duración en milisegundos
        std::chrono::duration<double, std::milli> tiempo = fin - inicio;

        return tiempo.count();
    }
};