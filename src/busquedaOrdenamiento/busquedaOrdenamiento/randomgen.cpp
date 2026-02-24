#include "randomgen.h"
#include <iostream>
#include <algorithm>
#include <limits>

//Hola amikos ya este pedo ya esta creo si falla algo pasare todos los archivos que modifique paera que jalara al 100

using namespace std;

// Lee un entero con validación mínima para evitar que el programa se rompa por entrada inválida
static int leerEnteroSeguro(const string& prompt, int minPermitido)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= minPermitido) return x;

        cout << "Entrada invalida. Debe ser un entero >= " << minPermitido << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Lee un entero dentro de un rango [minV, maxV]
static int leerEnteroRango(const string& prompt, int minV, int maxV)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= minV && x <= maxV) return x;

        cout << "Entrada invalida. Debe estar entre " << minV << " y " << maxV << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//  Calcula el tamaño final del arreglo según opción (N, N*N, N*M)
std::size_t calcularTamano(int tipoTam, int N, int M)
{
    if (N < 1) N = 1;
    if (M < 1) M = 1;

    long long size = 0;
    if (tipoTam == 1) size = (long long)N;
    else if (tipoTam == 2) size = (long long)N * (long long)N;
    else if (tipoTam == 3) size = (long long)N * (long long)M;
    else size = (long long)N;

    // Liite de seguridad para que nadie meta N=100000 y congele todo
    const long long LIM = 5'000'000;
    if (size > LIM) size = LIM;

    return (size_t)size;
}

// Genera números aleatorios donde SE PUEDEN REPETIR (distribución uniforme)
std::vector<int> generarConRepetidos(std::size_t size, int minVal, int maxVal, std::mt19937& rng)
{
    if (minVal > maxVal) std::swap(minVal, maxVal);
    std::uniform_int_distribution<int> dist(minVal, maxVal);

    std::vector<int> v;
    v.reserve(size);

    for (size_t i = 0; i < size; ++i)
        v.push_back(dist(rng));

    return v;
}

//  Genera números aleatorios SIN REPETIR usando "pool + shuffle"
std::vector<int> generarSinRepetidos(std::size_t size, int minVal, int maxVal, std::mt19937& rng)
{
    if (minVal > maxVal) std::swap(minVal, maxVal);

    // 0/ Asegurar que el rango tenga suficientes valores únicos
    long long rango = (long long)maxVal - (long long)minVal + 1LL;
    if (rango < (long long)size)
    {
        // 0/ Ajuste automático del máximo para permitir size valores únicos
        maxVal = minVal + (int)size - 1;
    }

    std::vector<int> pool;
    pool.reserve((size_t)((long long)maxVal - (long long)minVal + 1LL));

    for (int x = minVal; x <= maxVal; ++x)
        pool.push_back(x);

    std::shuffle(pool.begin(), pool.end(), rng);

    pool.resize(size);
    return pool;
}

// Menú para que el usuario elija tamaño (N, N*N, N*M) y repetidos/sin repetidos
std::vector<int> generarArregloInteractivo_(int& outN)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    cout << "\n=== GENERADOR DE ARREGLOS ALEATORIOS ===\n";
    cout << "Tamanos disponibles:\n";
    cout << "1) N\n";
    cout << "2) N*N\n";
    cout << "3) N*M\n";

    int tipo = leerEnteroRango("Elige tipo (1-3): ", 1, 3);
    int N = leerEnteroSeguro("Ingresa N (>=1): ", 1);
    int M = 1;
    if (tipo == 3) M = leerEnteroSeguro("Ingresa M (>=1): ", 1);

    size_t size = calcularTamano(tipo, N, M);

    cout << "\nModo de generacion:\n";
    cout << "1) Permitir repetidos\n";
    cout << "2) NO permitir repetidos\n";
    int modo = leerEnteroRango("Elige modo (1-2): ", 1, 2);

    cout << "\nDefine el rango de valores:\n";
    int minVal = leerEnteroSeguro("Min: ", -1'000'000);
    int maxVal = leerEnteroSeguro("Max: ", -1'000'000);

    std::vector<int> arr;
    if (modo == 1) arr = generarConRepetidos(size, minVal, maxVal, rng);
    else           arr = generarSinRepetidos(size, minVal, maxVal, rng);

    outN = (int)size;
    cout << "Arreglo generado con tamano: " << outN << "\n";
    return arr;
}