// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

using namespace std;

void resuelve(const vector<int>& tipos, const vector<int>& cantidades, const int& precio) {
	int n = tipos.size() - 1;
	Matriz<int> matriz(n + 1, precio + 1, 1E9);

	matriz[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= precio; j++) {
			if (tipos[i] > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else{
				int min_ = 1E9;
				int k = 0;
				while (k <= cantidades[i] && k*tipos[i] <= j) {
					min_ = min(min_, matriz[i - 1][j - k * tipos[i]] + k);
					k++;
				}

				matriz[i][j] = min_;
			}
		}
	}

	matriz[n][precio] != 1E9 ? cout <<"SI " << matriz[n][precio] << endl : cout << "NO" << endl;
};

void resuelve2(const vector<int>& tipos, const vector<int>& cantidades, const int& precio) {
	int n = cantidades.size() - 1;
	vector<int> matriz(precio + 1, 1E9);

	matriz[0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[0] = 0;
		for (int j = precio; j >= 0; j--) {
			if (tipos[i] > j) {
				matriz[j] = matriz[j];
			}
			else {
				int min_ = 1E9;
				int k = 0;
				while (k <= cantidades[i] && k*tipos[i] <= j) {
					min_ = min(min_, matriz[j - k * tipos[i]] + k);
					k++;
				}

				matriz[j] = min_;
			}
		}
	}

	matriz[precio] != 1E9 ? cout << "SI " << matriz[precio] << endl : cout << "NO" << endl;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (!std::cin)
        return false;

	vector<int> tipos(N + 1);
	for (size_t i = 1; i <= N; i++){
		int t;
		cin >> t;
		tipos[i] = (t);
	}
	vector<int> cant(N + 1);
	for (size_t i = 1; i <= N; i++) {
		int t;
		cin >> t;
		cant[i] = (t);
	}

	int precio; 
	cin >> precio;
    
	resuelve2(tipos, cant, precio);
    // escribir sol
    
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}