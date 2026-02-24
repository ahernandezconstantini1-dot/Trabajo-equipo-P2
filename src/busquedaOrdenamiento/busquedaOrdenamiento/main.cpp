/**
 * @page complejidad_analisis Análisis de Complejidad - Responsable: Mau
 *
 * @section resumen_general Resumen General del Programa
 *
 * @subsection complejidad_tiempo Complejidad Temporal Global
 * <table>
 * <tr><th>Escenario</th><th>Complejidad</th><th>Condición</th></tr>
 * <tr>
 *   <td><b>Peor caso</b></td>
 *   <td>O(k × n²)</td>
 *   <td>Usuario usa siempre ordenamientos cuadráticos (Burbuja, Selección)</td>
 * </tr>
 * <tr>
 *   <td><b>Caso promedio</b></td>
 *   <td>O(k × n log n)</td>
 *   <td>Usuario usa QuickSort o MergeSort predominantemente</td>
 * </tr>
 * <tr>
 *   <td><b>Mejor caso</b></td>
 *   <td>O(k × n)</td>
 *   <td>Solo búsquedas secuenciales sin ordenamiento previo</td>
 * </tr>
 * </table>
 * Donde: k = iteraciones del menú, n = tamaño del arreglo
 *
 * @subsection complejidad_espacio Complejidad Espacial Global
 * - **Datos:** O(n) - Arreglo principal
 * - **Auxiliar:** O(n) peor caso (MergeSort) o O(log n) (QuickSort)
 * - **Total:** O(n)
 *
 * @section complejidad_por_case Complejidad por Case
 *
 * | Case | Descripción | Temporal | Espacial |
 * |------|-------------|----------|----------|
 * | 0 | Regenerar arreglo | O(n) | O(n) |
 * | 1 | Búsqueda secuencial | **O(n)** | O(1) |
 * | 2 | Burbuja + Binaria | **O(n²)** | O(1) |
 * | 3 | Menú ordenamiento | O(n²) a O(n log n) | O(1) a O(n) |
 * | 4 | Benchmarks automáticos | Variable | O(n) |
 * | 5 | Salir | O(1) | O(1) |
 *
 * @section notas_implementacion Notas de Implementación
 * - Case 2 tiene cuello de botella en Burbuja O(n²)
 * - Case 3 método 4 (QuickSort) puede degradar a O(n²) con datos ordenados
 * - Case 3 método 5 (MergeSort) es el único con garantía O(n log n)
 * - Case 4 ejecuta benchmarks automáticos exportando a CSV
 */

 /**
  * @file main.cpp
  * @brief Programa principal unificado: demostración interactiva + benchmarks de algoritmos
  * @author Equipo de Desarrollo
  * @date 2024
  *
  * @section complejidad COMPLEJIDAD GLOBAL DEL PROGRAMA
  *
  * @subsection tiempo COMPLEJIDAD TEMPORAL
  * - **Peor caso:** O(k × n²) cuando el usuario selecciona repetidamente
  *   métodos de ordenamiento cuadráticos (Burbuja, Selección, Inserción)
  * - **Caso promedio:** O(k × n log n) utilizando QuickSort o MergeSort
  * - **Mejor caso:** O(k × n) con búsquedas secuenciales sin ordenamiento
  * - Donde k = número de operaciones del usuario (iteraciones del menú)
  *
  * @subsection espacio COMPLEJIDAD ESPACIAL
  * - **Arreglo de datos:** O(n) donde n es el tamaño del arreglo
  * - **Stack de recursión (QuickSort):** O(log n) promedio, O(n) peor caso
  * - **Stack de recursión (MergeSort):** O(log n)
  * - **Vector temporal (MergeSort):** O(n)
  * - **Total auxiliar:** O(n) en el peor caso (MergeSort)
  */

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
#include <limits>
using namespace std;

#include "search.h"
#include "sort.h"
#include "view.h"

using Clock = std::chrono::high_resolution_clock;

/**
 * @struct Stats
 * @brief Estructura para almacenar estadísticas de rendimiento
 * @complexity O(1) - Solo almacena 4 valores double
 */
struct Stats {
    double promedio_ms;      ///< Promedio de tiempo en milisegundos
    double desviacion_ms;    ///< Desviación estándar
    double min_ms;           ///< Tiempo mínimo registrado
    double max_ms;           ///< Tiempo máximo registrado
};

/**
 * @brief Generador de números aleatorios global (singleton)
 * @return std::mt19937& Referencia al generador inicializado
 * @complexity O(1) - Inicialización lazy una sola vez
 */
static std::mt19937& rngGlobal() {
    static std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

/**
 * @brief Genera un arreglo de enteros aleatorios
 * @param n Tamaño del arreglo
 * @param minVal Valor mínimo (default: 1)
 * @param maxVal Valor máximo (default: 100000)
 * @return std::vector<int> Vector con valores aleatorios
 *
 * @complexity O(n) - Genera n números aleatorios secuencialmente
 * @spacecomplexity O(n) - Almacena n enteros en el vector
 */
std::vector<int> generarArreglo(int n, int minVal = 1, int maxVal = 100000)
{
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rngGlobal());
    return a;
}

/**
 * @brief Mide el tiempo de una única ejecución de función
 * @param fn Función a medir (lambda o std::function)
 * @return double Tiempo en milisegundos
 *
 * @complexity O(1) respecto a la medición, O(T(fn)) respecto a la función medida
 */
double medirUnaCorridaMs(const std::function<void()>& fn)
{
    auto t0 = Clock::now();
    fn();
    auto t1 = Clock::now();
    std::chrono::duration<double, std::milli> dt = t1 - t0;
    return dt.count();
}

/**
 * @brief Mide estadísticas de rendimiento sobre múltiples ejecuciones
 * @param fn Función a benchmarkear
 * @param repeticiones Número de repeticiones para estadísticas
 * @param warmup Repeticiones de calentamiento (default: 1)
 * @return Stats Estadísticas calculadas
 *
 * @complexity O(repeticiones × T(fn)) - Ejecuta fn múltiples veces
 * @spacecomplexity O(repeticiones) - Almacena tiempos en vector temporal
 */
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

/**
 * @brief Ejecuta benchmarks automáticos y exporta resultados a CSV
 *
 * @complexity Variable según los tamaños de prueba:
 * - Para cada tamaño n: O(n²) métodos cuadráticos, O(n log n) eficientes
 * - Total: O(Σ(n² + n log n)) para todos los tamaños de prueba
 *
 * @spacecomplexity O(n) - Crea copias temporales del arreglo para cada prueba
 *
 * @details
 * Ejecuta todos los algoritmos con tamaños predefinidos (1000, 5000, 10000)
 * y exporta estadísticas detalladas a resultados.csv
 */
void ejecutarBenchmarks()
{
    // Tamaños de prueba: N, N*N, N*M (ejemplo: 1000, 5000, 10000)
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

        /// @complexity O(n²) - Burbuja cuadrático
        medirOrdenamiento("Burbuja", [&](std::vector<int>& a) {
            ordenarBurbuja(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n²) - Selección cuadrático
        medirOrdenamiento("Seleccion", [&](std::vector<int>& a) {
            ordenarSeleccion(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n²) peor, O(n) mejor - Inserción adaptable
        medirOrdenamiento("Insercion", [&](std::vector<int>& a) {
            ordenarInsercion(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n log n) promedio, O(n²) peor - QuickSort
        medirOrdenamiento("QuickSort", [&](std::vector<int>& a) {
            int comp = 0, inter = 0;
            quickSort(a.data(), 0, (int)a.size() - 1, comp, inter, false);
            });

        /// @complexity O(n log n) garantizado - MergeSort
        medirOrdenamiento("MergeSort", [&](std::vector<int>& a) {
            int comp = 0;
            mergeSort(a.data(), 0, (int)a.size() - 1, comp, false);
            });

        // Búsqueda Secuencial
        {
            int valor = base[n / 2];
            Stats s = medirVariasCorridasMs([&]() {
                busquedaSecuencial(base.data(), (int)base.size(), valor, false);
                }, repeticiones);

            std::cout << "BusquedaSecuencial -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaSecuencial" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }

        // Búsqueda Binaria
        {
            std::vector<int> ordenado = base;
            std::sort(ordenado.begin(), ordenado.end());
            int valor = ordenado[n / 2];

            Stats s = medirVariasCorridasMs([&]() {
                busquedaBinaria(ordenado.data(), (int)ordenado.size(), valor, false);
                }, repeticiones);

            std::cout << "BusquedaBinaria -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaBinaria" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }
    }

    csv.close();
    std::cout << "\nListo. Se generó: resultados.csv\n";
}

/**
 * @brief Menú interactivo para generar arreglos con diferentes configuraciones
 * @param outN Parámetro de salida con el tamaño final del arreglo
 * @return std::vector<int> Arreglo generado según especificaciones del usuario
 *
 * @complexity O(n) o O(rango) según el modo seleccionado
 * @spacecomplexity O(n) - Retorna vector del tamaño solicitado
 */
std::vector<int> generarArregloInteractivo(int& outN)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    cout << "\n=== GENERADOR DE ARREGLOS ALEATORIOS ===\n";
    cout << "Tamanos disponibles:\n";
    cout << "1) N\n";
    cout << "2) N*N\n";
    cout << "3) N*M\n";

    auto leerEnteroRango = [&](const string& prompt, int minV, int maxV) -> int {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minV && x <= maxV) return x;
            cout << "Entrada invalida. Debe estar entre " << minV << " y " << maxV << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        };

    auto leerEnteroSeguro = [&](const string& prompt, int minPermitido) -> int {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minPermitido) return x;
            cout << "Entrada invalida. Debe ser un entero >= " << minPermitido << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        };

    int tipo = leerEnteroRango("Elige tipo (1-3): ", 1, 3);
    int N = leerEnteroSeguro("Ingresa N (>=1): ", 1);
    int M = 1;
    if (tipo == 3) M = leerEnteroSeguro("Ingresa M (>=1): ", 1);

    // Calcular tamaño: N, N*N, o N*M
    long long size = 0;
    if (tipo == 1) size = (long long)N;
    else if (tipo == 2) size = (long long)N * (long long)N;
    else size = (long long)N * (long long)M;

    // Límite de seguridad: 5 millones de elementos
    const long long LIM = 5'000'000;
    if (size > LIM) size = LIM;

    cout << "\nModo de generacion:\n";
    cout << "1) Permitir repetidos\n";
    cout << "2) NO permitir repetidos\n";
    int modo = leerEnteroRango("Elige modo (1-2): ", 1, 2);

    cout << "\nDefine el rango de valores:\n";
    int minVal = leerEnteroSeguro("Min: ", -1'000'000);
    int maxVal = leerEnteroSeguro("Max: ", -1'000'000);

    std::vector<int> arr;
    arr.reserve((size_t)size);

    if (modo == 1) {
        // Con repetidos: O(n)
        if (minVal > maxVal) std::swap(minVal, maxVal);
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        for (size_t i = 0; i < (size_t)size; ++i)
            arr.push_back(dist(rng));
    }
    else {
        // Sin repetidos: O(rango) donde rango = maxVal - minVal + 1
        if (minVal > maxVal) std::swap(minVal, maxVal);
        long long rango = (long long)maxVal - (long long)minVal + 1LL;
        if (rango < size) maxVal = minVal + (int)size - 1;

        std::vector<int> pool;
        for (int x = minVal; x <= maxVal; ++x) pool.push_back(x);
        std::shuffle(pool.begin(), pool.end(), rng);
        pool.resize((size_t)size);
        arr = std::move(pool);
    }

    outN = (int)size;
    cout << "Arreglo generado con tamano: " << outN << "\n";
    return arr;
}

/**
 * @brief Punto de entrada principal del programa
 * @return int Código de salida (0 = éxito)
 *
 * @complexity
 * | Aspecto | Complejidad | Descripción |
 * |---------|-------------|-------------|
 * | Tiempo (peor) | O(k × n²) | k iteraciones con ordenamiento O(n²) |
 * | Tiempo (prom) | O(k × n log n) | k iteraciones con ordenamiento óptimo |
 * | Tiempo (mejor)| O(k × n) | Solo búsquedas secuenciales |
 * | Espacio | O(n) | Arreglo dinámico + overhead de recursión |
 *
 * @note El programa opera en un bucle interactivo donde k representa
 *       la cantidad de operaciones que el usuario realiza antes de salir.
 */
int main()
{
    int opcion;
    int metodo;

    /// @brief Arreglo dinámico para soportar tamaños N, N*N, N*M
    vector<int> arregloVec;
    int n = 0;

    /// @brief Flag para activar/desactivar modo verbose (paso a paso)
    bool verbose = false;

    /// @brief Variables para métricas de QuickSort y MergeSort
    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

    /**
     * @brief Inicialización: Generación del arreglo aleatorio
     * @complexity O(n) donde n depende de la opción seleccionada (N, N², N×M)
     * @spacecomplexity O(n) para almacenar el vector generado
     */
    arregloVec = generarArregloInteractivo(n);

    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
            /**
             * @case CASE_0_REGENERAR
             * @brief Regenera el arreglo con nuevos parámetros
             *
             * @complexity
             * - **Temporal:** O(n) para generar el nuevo arreglo
             * - **Espacial:** O(n) para el nuevo vector (el anterior se libera)
             *
             * @details
             * Permite al usuario especificar:
             * - Tamaño: N, N×N, o N×M
             * - Modo: Con repetidos (uniforme) o sin repetidos (shuffle)
             * - Rango: Valores mínimos y máximos
             */
        case 0:
            arregloVec = generarArregloInteractivo(n);
            cout << "Mostrar proceso paso a paso? (1=Si / 0=No): ";
            cin >> verbose;
            break;

            /**
             * @case CASE_1_BUSQUEDA_SECUENCIAL
             * @brief Realiza búsqueda lineal en el arreglo
             *
             * @complexity
             * | Operación | Complejidad | Notación Big-O |
             * |-----------|-------------|----------------|
             * | mostrarArreglo() | Lineal | O(n) |
             * | pedirValor() | Constante | O(1) |
             * | busquedaSecuencial() | Lineal | **O(n)** |
             * | Impresión resultado | Constante | O(1) |
             * | **TOTAL** | **Lineal** | **O(n)** |
             *
             * @complexity_detailed
             * - **Peor caso:** O(n) - elemento no existe o está al final
             * - **Mejor caso:** O(1) - elemento en primera posición
             * - **Caso promedio:** O(n/2) = O(n) - asumiendo distribución uniforme
             *
             * @spacecomplexity O(1) - Solo usa índices auxiliares
             *
             * @pre El arreglo puede estar en cualquier estado (no requiere orden)
             * @post Posición del elemento encontrado o -1 si no existe
             *
             * @invariant Se mantiene: 0 ≤ índice < n durante la búsqueda
             */
        case 1:
            mostrarArreglo(arregloVec.data(), n);
            valor = pedirValor();
            posicion = busquedaSecuencial(arregloVec.data(), n, valor, verbose);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

            /**
             * @case CASE_2_BUSQUEDA_BINARIA
             * @brief Ordena con Burbuja y realiza búsqueda binaria
             *
             * @complexity
             * | Operación | Complejidad | Detalle Matemático |
             * |-----------|-------------|-------------------|
             * | ordenarBurbuja() | Cuadrática | **O(n²)** - Σ(i=1 to n-1) i = n(n-1)/2 |
             * | mostrarArreglo() | Lineal | O(n) |
             * | pedirValor() | Constante | O(1) |
             * | busquedaBinaria() | Logarítmica | **O(log n)** - ⌊log₂(n)⌋+1 iteraciones |
             * | **TOTAL** | **Cuadrática** | **O(n²)** ← Dominada por Burbuja |
             *
             * @complexity_detailed
             * **Análisis de ordenarBurbuja():**
             * - Comparaciones: n(n-1)/2 = Θ(n²) (siempre, sin optimización de bandera)
             * - Intercambios: 0 a n(n-1)/2 dependiendo del desorden inicial
             * - Pasadas: n-1 garantizadas
             *
             * **Análisis de busquedaBinaria():**
             * - Iteraciones máximas: ⌊log₂(n)⌋ + 1
             * - Ejemplos: n=1,000→10, n=1,000,000→20, n=10⁹→30 iteraciones
             *
             * @spacecomplexity O(1) - Ordenamiento in-place, búsqueda con índices
             *
             * @pre El arreglo puede estar desordenado (se ordena internamente)
             * @post Arreglo ordenado ascendentemente + posición del valor buscado
             *
             * @warning El cuello de botella es ordenarBurbuja() con O(n²).
             *          Para n > 10,000, considerar usar Case 3 con QuickSort/MergeSort
             *          y luego busquedaBinaria() manualmente.
             *
             * @invariant_post_ordenamiento Para todo i, 0 ≤ i < n-1: A[i] ≤ A[i+1]
             */
        case 2:
            cout << "\nOrdenando arreglo con burbuja...\n";
            ordenarBurbuja(arregloVec.data(), n, verbose);
            mostrarArreglo(arregloVec.data(), n);

            valor = pedirValor();
            posicion = busquedaBinaria(arregloVec.data(), n, valor, verbose);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

            /**
             * @case CASE_3_MENU_ORDENAMIENTO
             * @brief Menú de selección de algoritmos de ordenamiento
             *
             * @complexity Variable según método seleccionado:
             *
             * | Método | # | Temporal | Espacial | Estable | In-place |
             * |--------|---|----------|----------|---------|----------|
             * | Burbuja | 1 | **O(n²)** | O(1) | Sí | Sí |
             * | Selección | 2 | **O(n²)** | O(1) | No | Sí |
             * | Inserción | 3 | O(n²) peor, **O(n)** mejor | O(1) | Sí | Sí |
             * | QuickSort | 4 | **O(n log n)** avg, O(n²) peor | O(log n) avg | No | Sí |
             * | MergeSort | 5 | **O(n log n)** garantizado | O(n) | Sí | No |
             *
             * @complexity_detailed
             *
             * **Método 1 - Burbuja (Bubble Sort):**
             * - Fórmula: T(n) = n(n-1)/2 comparaciones + swaps
             * - Siempre Θ(n²) - no detecta arreglo ordenado
             *
             * **Método 2 - Selección (Selection Sort):**
             * - Comparaciones: SIEMPRE n(n-1)/2 (no tiene mejor caso)
             * - Intercambios: EXACTAMENTE n-1 (mínimo posible)
             * - Útil cuando los swaps son costosos (ej: escritura en disco)
             *
             * **Método 3 - Inserción (Insertion Sort):**
             * - Peor caso (inverso): n(n-1)/2 comparaciones y movimientos
             * - Mejor caso (ordenado): n-1 comparaciones, 0 movimientos
             * - Excelente para datos "casi ordenados" (desplazamiento pequeño)
             *
             * **Método 4 - QuickSort:**
             * - Recurrencia promedio: T(n) = 2T(n/2) + O(n) → O(n log n)
             * - Recurrencia peor caso: T(n) = T(n-1) + O(n) → O(n²)
             * - Peor caso ocurre con: arreglo ordenado + pivote central fijo
             * - Espacio de pila: O(log n) promedio, O(n) peor caso recursivo
             *
             * **Método 5 - MergeSort:**
             * - Recurrencia: T(n) = 2T(n/2) + O(n) → Θ(n log n) (Teorema Maestro, caso 2)
             * - Árbol de recursión: log₂(n) niveles × n trabajo por nivel
             * - Espacio adicional: O(n) para vector temporal en merge
             * - Único método que garantiza O(n log n) sin depender de entrada
             *
             * @spacecomplexity
             * - Métodos 1-4: O(1) auxiliar (in-place)
             * - Método 5: O(n) auxiliar (vector temporal)
             * - Stack recursión (4-5): O(log n) típico
             *
             * @pre El arreglo puede estar en cualquier estado
             * @post Arreglo ordenado ascendentemente según el método elegido
             *
             * @recommendations
             * - **n < 50:** Cualquier método (simpleza > eficiencia)
             * - **n < 1000, casi ordenado:** Inserción (O(n) efectivo)
             * - **n grande, memoria limitada:** QuickSort (más rápido promedio)
             * - **n grande, necesita estabilidad:** MergeSort (garantizado O(n log n))
             * - **Evitar:** Burbuja para cualquier n > 100 (puramente educativo)
             *
             * @invariant Todos los métodos garantizan:
             *            ∀i ∈ [0, n-2]: arreglo[i] ≤ arreglo[i+1]
             */
        case 3:
            metodo = mostrarMenuOrdenamiento();
            comparaciones = 0;
            intercambios = 0;

            if (metodo == 1)
            {
                /// @complexity O(n²) - Burbuja siempre cuadrático
                ordenarBurbuja(arregloVec.data(), n, verbose);
            }
            else if (metodo == 2)
            {
                /// @complexity O(n²) - Selección siempre cuadrático
                ordenarSeleccion(arregloVec.data(), n, verbose);
            }
            else if (metodo == 3)
            {
                /// @complexity O(n²) peor, O(n) mejor - Inserción adaptable
                ordenarInsercion(arregloVec.data(), n, verbose);
            }
            else if (metodo == 4)
            {
                /// @complexity O(n log n) promedio, O(n²) peor - QuickSort
                /// @spacecomplexity O(log n) pila de recursión promedio
                quickSort(arregloVec.data(), 0, n - 1, comparaciones, intercambios, verbose);
                cout << "Comparaciones: " << comparaciones << endl;
                cout << "Intercambios: " << intercambios << endl;
            }
            else if (metodo == 5)
            {
                /// @complexity O(n log n) garantizado - MergeSort
                /// @spacecomplexity O(n) vector temporal + O(log n) pila
                mergeSort(arregloVec.data(), 0, n - 1, comparaciones, verbose);
                cout << "Comparaciones: " << comparaciones << endl;
            }
            else
            {
                /// @complexity O(1) - Manejo de entrada inválida
                cout << "Metodo invalido.\n";
            }

            cout << "\nArreglo ordenado:\n";
            mostrarArreglo(arregloVec.data(), n);
            break;

            /**
             * @case CASE_4_BENCHMARKS
             * @brief Ejecuta benchmarks automáticos y exporta a CSV
             *
             * @complexity Variable: O(Σ(n² + n log n)) para todos los tamaños de prueba
             * @spacecomplexity O(n) - Crea copias temporales para cada prueba
             *
             * @details Ejecuta todos los algoritmos con tamaños predefinidos
             *          (1000, 5000, 10000) y genera resultados.csv con estadísticas.
             */
        case 4:
            ejecutarBenchmarks();
            break;

            /**
             * @case CASE_5_SALIR
             * @brief Termina la ejecución del programa
             *
             * @complexity O(1) - Operación de salida constante
             * @spacecomplexity O(1) - Liberación automática de recursos (vector)
             */
        case 5:
            cout << "Saliendo...\n";
            break;

            /**
             * @case DEFAULT_OPCION_INVALIDA
             * @brief Manejo de opción de menú no reconocida
             *
             * @complexity O(1) - Impresión de error constante
             */
        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    /**
     * @brief Liberación de recursos
     * @complexity O(1) - El vector se destruye automáticamente al salir del scope
     * @spacecomplexity O(1) - Liberación de memoria dinámica del vector
     */
    return 0;
}