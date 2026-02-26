#include "controller.h"
#include "search.h"
#include "sort.h"
#include "view.h"
#include "randomgen.h"
#include <iostream>
#include <vector>

using namespace std;

void iniciarAplicacion() {
    int opcion, metodo, n = 0, valor, posicion, comparaciones, intercambios;
    vector<int> arregloVec;
    bool verbose = false;

    arregloVec = generarArregloInteractivo(n); //

    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
        case 1: // Búsqueda Secuencial
            valor = pedirValor();
            posicion = busquedaSecuencial(arregloVec.data(), n, valor, verbose);
            // ... lógica de impresión ...
            break;
        case 3: // Ordenamiento
            metodo = mostrarMenuOrdenamiento();
            // ... lógica de selección de algoritmos (Burbuja, QuickSort, etc) ...
            break;
            // Otros casos migrados de main.cpp original
        }
    } while (opcion != 4);
}