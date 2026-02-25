#pragma once
#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <vector>
#include <random>

//Este pedin es la parte que jala pero tengo que modificar los demás archivos
//Recordar


// 0/ Calcula el tamaño final según el tipo elegido: 1=N, 2=N*N, 3=N*M
std::size_t calcularTamano(int tipoTam, int N, int M);

// 0/ Genera un vector de tamaño "size" con valores aleatorios (SE PERMITEN REPETIDOS)
std::vector<int> generarConRepetidos(std::size_t size, int minVal, int maxVal, std::mt19937& rng);

// 0/ Genera un vector de tamaño "size" con valores aleatorios (NO SE PERMITEN REPETIDOS)
// 0/ Si el rango es insuficiente, se ajusta automáticamente para que alcance.
std::vector<int> generarSinRepetidos(std::size_t size, int minVal, int maxVal, std::mt19937& rng);

// 0/ Menú interactivo: pide N/M, tipo de tamaño y modo repetidos/no repetidos y regresa el arreglo.
std::vector<int> generarArregloInteractivo_(int& outN);

#endif