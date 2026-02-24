#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
using namespace std;

#include "search.h"
#include "sort.h"
#include "view.h"


using Clock = std::chrono::high_resolution_clock;

struct Stats {
    double promedio_ms;
    double desviacion_ms;
    double min_ms;
    double max_ms;
};

static std::mt19937& rngGlobal() {
    static std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

std::vector<int> generarArreglo(int n, int minVal = 1, int maxVal = 100000)
{
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rngGlobal());
    return a;
}

double medirUnaCorridaMs(const std::function<void()>& fn)
{
    auto t0 = Clock::now();
    fn();
    auto t1 = Clock::now();
    std::chrono::duration<double, std::milli> dt = t1 - t0;
    return dt.count();
}

Stats medirVariasCorridasMs(const std::function<void()>& fn, int repeticiones, int warmup = 1)
{
    for (int i = 0; i < warmup; i++) fn();

    std::vector<double> t;
    t.reserve(repeticiones);

    for (int i = 0; i < repeticiones; i++)
        t.push_back(medirUnaCorridaMs(fn));

    double prom = std::accumulate(t.begin(), t.end(), 0.0) / t.size();

    double var = 0.0;
    for (double x : t) var += (x - prom) * (x - prom);
    var /= t.size();

    double mn = *std::min_element(t.begin(), t.end());
    double mx = *std::max_element(t.begin(), t.end());

    return { prom, std::sqrt(var), mn, mx };
}

void ejecutarBenchmarks()
{
    // Cambia estos 3 valores a los que tu equipo defina como N, NN, NM
    std::vector<int> tamanios = { 1000, 5000, 10000 };
    int repeticiones = 10;

    std::ofstream csv("resultados.csv");
    csv << "algoritmo,n,promedio_ms,desviacion_ms,min_ms,max_ms\n";
    csv << std::fixed << std::setprecision(6);

    std::cout << "\n=== BENCHMARKS (tiempos en ms) ===\n";

    for (int n : tamanios)
    {
        std::cout << "\n--- n = " << n << " ---\n";

        std::vector<int> base = generarArreglo(n);

        auto medirOrdenamiento = [&](const std::string& nombre, auto sortFn)
        {
            Stats s = medirVariasCorridasMs([&]() {
                std::vector<int> a = base;
                sortFn(a);
            }, repeticiones);

            std::cout << nombre << " -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << nombre << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        };

        medirOrdenamiento("Burbuja", [&](std::vector<int>& a) { ordenarBurbuja(a.data(), (int)a.size()); });
        medirOrdenamiento("Seleccion", [&](std::vector<int>& a) { ordenarSeleccion(a.data(), (int)a.size()); });
        medirOrdenamiento("Insercion", [&](std::vector<int>& a) { ordenarInsercion(a.data(), (int)a.size()); });

        medirOrdenamiento("QuickSort", [&](std::vector<int>& a) {
            int comp = 0, inter = 0;
            quickSort(a.data(), 0, (int)a.size() - 1, comp, inter);
        });

        medirOrdenamiento("MergeSort", [&](std::vector<int>& a) {
            int comp = 0;
            mergeSort(a.data(), 0, (int)a.size() - 1, comp);
        });

        // Búsquedas
        {
            int valor = base[n / 2];
            Stats s = medirVariasCorridasMs([&]() {
                busquedaSecuencial(base.data(), (int)base.size(), valor);
            }, repeticiones);

            std::cout << "BusquedaSecuencial -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaSecuencial" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }

        {
            std::vector<int> ordenado = base;
            std::sort(ordenado.begin(), ordenado.end());
            int valor = ordenado[n / 2];

            Stats s = medirVariasCorridasMs([&]() {
                busquedaBinaria(ordenado.data(), (int)ordenado.size(), valor);
            }, repeticiones);

            std::cout << "BusquedaBinaria -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaBinaria" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }
    }

    csv.close();
    std::cout << "\nListo. Se generó: resultados.csv (mandaselo a Diego)\n";
}

int main()
{
    int opcion;
    int metodo;
    int arreglo[10] = { 33, 5, 90, 12, 41, 8, 77, 20, 50, 62 };
    int n = 10;
    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                mostrarArreglo(arreglo, n);
                valor = pedirValor();
                posicion = busquedaSecuencial(arreglo, n, valor);

                if (posicion != -1)
                {
                    cout << "Valor encontrado en posicion: " << posicion << endl;
                }
                else
                {
                    cout << "Valor no encontrado.\n";
                }
                break;

            case 2:
                cout << "\nOrdenando arreglo...\n";
                ordenarBurbuja(arreglo, n);
                mostrarArreglo(arreglo, n);

                valor = pedirValor();
                posicion = busquedaBinaria(arreglo, n, valor);

                if (posicion != -1)
                {
                    cout << "Valor encontrado en posicion: " << posicion << endl;
                }
                else
                {
                    cout << "Valor no encontrado.\n";
                }   
                break;

            case 3:

                metodo = mostrarMenuOrdenamiento();
                
                
                if (metodo == 1)
                {
                    ordenarBurbuja(arreglo, n);
                }
                else if (metodo == 2)
                {
                    ordenarSeleccion(arreglo, n);
                }
                else if (metodo == 3)
                {
                    ordenarInsercion(arreglo, n);
                }
                else if (metodo == 4)
                {
                    quickSort(arreglo, 0, n - 1, comparaciones, intercambios);
                    cout << "Comparaciones: " << comparaciones << endl;
                    cout << "Intercambios: " << intercambios << endl;
                }
                else if (metodo == 5)
                {
                    mergeSort(arreglo, 0, n - 1, comparaciones);
                    cout << "Comparaciones: " << comparaciones << endl;
                }
                else
                {
                    cout << "Metodo invalido.\n";
                }

                cout << "\nArreglo ordenado:\n";
                mostrarArreglo(arreglo, n);
                break;

            case 4:
                ejecutarBenchmarks();
                break;

            case 5:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}
