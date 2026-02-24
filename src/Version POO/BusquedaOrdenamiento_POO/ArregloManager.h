/**
 * @file ArregloManager.h
 * @brief Definición de la clase ArregloManager para la administración de datos.
 * @author Luis (Diego)
 * @date 2026-02-24
 */

#pragma once
#ifndef ARREGLO_MANAGER_H
#define ARREGLO_MANAGER_H

#include <vector>
#include <string>

 /**
  * @class ArregloManager
  * @brief Clase encargada de la gestión, generación y visualización de datos.
  * @details Esta clase encapsula un vector dinámico de enteros y proporciona herramientas
  * para su creación mediante menús interactivos, asegurando la integridad de los datos.
  */
class ArregloManager {
private:
    std::vector<int> datos; /**< Vector que almacena los números enteros del arreglo. */
    int n; /**< Cantidad de elementos actualmente almacenados. */

    /**
     * @brief Método auxiliar para leer un entero de forma segura desde consola.
     * @details Proviene de la lógica original de randomgen.cpp.
     * @param prompt Mensaje que se muestra al usuario antes de la captura.
     * @param minPermitido Valor mínimo aceptado para la entrada.
     * @return El entero validado.
     */
    int leerEnteroSeguro(const std::string& prompt, int minPermitido);

    /**
     * @brief Método auxiliar para validar una entrada dentro de un rango.
     * @details Proviene de la lógica original de randomgen.cpp.
     * @param prompt Mensaje de instrucción.
     * @param minV Límite inferior permitido.
     * @param maxV Límite superior permitido.
     * @return El entero validado dentro del rango.
     */
    int leerEnteroRango(const std::string& prompt, int minV, int maxV);

public:
    /**
     * @brief Constructor por defecto de la clase.
     * @details Inicializa los atributos en un estado vacío.
     */
    ArregloManager();

    /** * @brief Genera el arreglo usando el menú interactivo original.
     * @details Permite definir el tamaño y si se aceptan duplicados o no.
     */
    void generarInteractivo();

    /** * @brief Muestra el contenido del arreglo en consola.
     * @details Incluye una restricción visual para no saturar la pantalla con arreglos gigantes.
     */
    void mostrar() const;

    /** * @brief Obtiene el puntero a los datos crudos del vector.
     * @return int* Puntero al primer elemento del arreglo interno.
     */
    int* getRawData() { return datos.data(); }

    /** * @brief Obtiene el tamaño del arreglo.
     * @return int Número de elementos.
     */
    int getTamano() const { return n; }

    /** * @brief Obtiene una referencia al vector de datos.
     * @return std::vector<int>& Referencia al contenedor original.
     */
    std::vector<int>& getVector() { return datos; }
};

#endif