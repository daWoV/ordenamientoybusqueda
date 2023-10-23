#include <iostream>
#include <fstream>
#include <vector>
//#include <ctime>
#include <cstdlib>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<int> ordenaIntercambio(vector<int> numeros) {
    int n = numeros.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                swap(numeros[j], numeros[j + 1]);
            }
        }
    }
    return numeros;
}

vector<int> ordenaBurbuja(vector<int> numeros) {
    int n = numeros.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                swap(numeros[j], numeros[j + 1]);
            }
        }
    }
    return numeros;
}

vector<int> merge(vector<int> izquierda, vector<int> derecha) {
    vector<int> resultado;
    int i = 0, j = 0;
    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i] < derecha[j]) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }
    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }
    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }
    return resultado;
}

vector<int> ordenaMerge(vector<int> numeros) {
    int n = numeros.size();
    if (n <= 1) {
        return numeros;
    }
    int mid = n / 2;
    vector<int> izquierda(numeros.begin(), numeros.begin() + mid);
    vector<int> derecha(numeros.begin() + mid, numeros.end());
    izquierda = ordenaMerge(izquierda);
    derecha = ordenaMerge(derecha);
    return merge(izquierda, derecha);
}

int busqSecuencial(vector<int> numeros, int dato) {
    for (int i = 0; i < numeros.size(); i++) {
        if (numeros[i] == dato) {
            return i;
        }
    }
    return -1;
}

int busqBinaria(vector<int> numeros, int dato) {
    int izquierda = 0;
    int derecha = numeros.size() - 1;
    while (izquierda <= derecha) {
        int mid = izquierda + (derecha - izquierda) / 2;
        if (numeros[mid] == dato) {
            return mid;
        }
        if (numeros[mid] < dato) {
            izquierda = mid + 1;
        } else {
            derecha = mid - 1;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << argv[0] << " <nombre_archivo> [numeros]" << endl;
        return 1;
    }

    vector<int> numeros;
    ifstream archivo(argv[1]);
    if (!archivo) {
        cout << "No se encontro el archivo." << endl;
        return 1;
    }
    int numero;
    while (archivo >> numero) {
        numeros.push_back(numero);
    }
    archivo.close();

    vector<int> ordenNumIntercambio = numeros;
    vector<int> ordenNumBurbuja = numeros;
    vector<int> ordenNumMerge = numeros;

    high_resolution_clock::time_point start_time, end_time;
    duration<double, milli> tiempoTranscurrido;

    start_time = high_resolution_clock::now();
    ordenNumIntercambio = ordenaIntercambio(ordenNumIntercambio);
    end_time = high_resolution_clock::now();
    tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
    double tiempoIntercambio = tiempoTranscurrido.count();

    start_time = high_resolution_clock::now();
    ordenNumBurbuja = ordenaBurbuja(ordenNumBurbuja);
    end_time = high_resolution_clock::now();
    tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
    double tiempoBurbuja = tiempoTranscurrido.count();

    start_time = high_resolution_clock::now();
    ordenNumMerge = ordenaMerge(ordenNumMerge);
    end_time = high_resolution_clock::now();
    tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
    double tiempoMerge = tiempoTranscurrido.count();

    if (ordenNumIntercambio == ordenNumBurbuja && ordenNumIntercambio == ordenNumMerge) {
        cout << "\n" << endl;
        cout << "Los vectores ordenados son iguales." << endl;
        cout << "-Datos ordenados:" << endl;
        for (int i = 0; i < ordenNumIntercambio.size(); i++) {
            cout << ordenNumIntercambio[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Los vectores ordenados NO son iguales. El programa se detendra." << endl;
        return 1;
    }

    cout << "\n" << endl;
    cout << "-Tiempos de ordenamiento:" << endl;
    cout << "Intercambio -> Tiempo: " << tiempoIntercambio << " ms" << endl;
    cout << "Burbuja     -> Tiempo: " << tiempoBurbuja << " ms" << endl;
    cout << "Merge       -> Tiempo: " << tiempoMerge << " ms" << endl;
    cout << "\n" << endl;
    cout << "-Tiempos de busqueda:" << endl;
    for (int i = 2; i < argc; i++) {
        int dato;
        istringstream(argv[i]) >> dato;
        cout << "\n" << endl;
        cout << "Entero buscando: " << dato << endl;

        start_time = high_resolution_clock::now();
        int indiceSecuencialOriginal = busqSecuencial(numeros, dato);
        end_time = high_resolution_clock::now();
        tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
        double tiempoBusqSecuencialOriginal = tiempoTranscurrido.count();

        if (indiceSecuencialOriginal != -1) {
            cout << "Secuencial en vector original: Encontrado en el indice " << indiceSecuencialOriginal << " en " << tiempoBusqSecuencialOriginal << " ms" << endl;
        } else {
            cout << "Secuencial en vector original: NO encontrado en " << tiempoBusqSecuencialOriginal << " ms" << endl;
        }

        start_time = high_resolution_clock::now();
        int indiceSecuencialOrdenado = busqSecuencial(ordenNumMerge, dato);
        end_time = high_resolution_clock::now();
        tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
        double tiempoBusqSecuencialOrdenado = tiempoTranscurrido.count();

        if (indiceSecuencialOrdenado != -1) {
            cout << "Secuencial en vector ordenado: Encontrado en el indice " << indiceSecuencialOrdenado << " en " << tiempoBusqSecuencialOrdenado << " ms" << endl;
        } else {
            cout << "Secuencial en vector ordenado: NO encontrado en " << tiempoBusqSecuencialOrdenado << " ms" << endl;
        }

        start_time = high_resolution_clock::now();
        int indiceBinariaOrdenado = busqBinaria(ordenNumMerge, dato);
        end_time = high_resolution_clock::now();
        tiempoTranscurrido = duration_cast<duration<double, milli>>(end_time - start_time);
        double tiempoBusqBinariaOrdenado = tiempoTranscurrido.count();

        if (indiceBinariaOrdenado != -1) {
            cout << "Busqueda binaria en vector ordenado: Encontrado en el indice " << indiceBinariaOrdenado << " en " << tiempoBusqBinariaOrdenado << " ms" << endl;
        } else {
            cout << "Busqueda binaria en vector ordenado: NO encontrado en " << tiempoBusqBinariaOrdenado << " ms" << endl;
        }
    }

    return 0;
}