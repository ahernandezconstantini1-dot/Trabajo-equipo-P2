#pragma once
#ifndef SEARCH_H
#define SEARCH_H

// 0/ verbose=true imprime el proceso paso a paso
int busquedaSecuencial(int arreglo[], int n, int valor, bool verbose = false);
int busquedaBinaria(int arreglo[], int n, int valor, bool verbose = false);

#endif