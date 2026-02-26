#pragma once
#ifndef SORT_H
#define SORT_H

// 0/ verbose=true imprime el proceso paso a paso
void ordenarBurbuja(int arreglo[], int n, bool verbose = false);
void ordenarSeleccion(int arreglo[], int n, bool verbose = false);
void ordenarInsercion(int arreglo[], int n, bool verbose = false);
void quickSort(int arreglo[], int izquierda, int derecha, int& comparaciones, int& intercambios, bool verbose = false);
void mergeSort(int arreglo[], int izquierda, int derecha, int& comparaciones, bool verbose = false);

#endif