// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void resuelve(const vector<pair<int, int>>& tesoros, const int& T) {
	int n = tesoros.size() - 1;
	Matriz<int> matriz(n + 1, T + 1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= T; j++) {
			if (3 * tesoros[i].first > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - 3 * tesoros[i].first] + tesoros[i].second);
			}
		}
	}

	cout << matriz[n][T] << endl;

	int j = T;
	int cuantos = 0;
	vector<bool> cuales(n + 1, false);
	for (int i = n; i > 0; i--) {
		if (matriz[i][j] == matriz[i - 1][j]) {
			//no lo cogemos
			cuales[i] = false;
		}
		else {
			//si lo cogemos
			cuantos++;
			cuales[i] = true;
			j -= 3 * tesoros[i].first;
		}
	}

	cout << cuantos << endl;
	for (size_t i = 0; i < cuales.size(); i++){
		if (cuales[i]) {
			cout << tesoros[i].first << " " << tesoros[i].second  << endl;
		}
	}

	cout << "----" << endl;

	/*vector<int> matriz(T + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = T; j > 0; j--) {
			if (3 * tesoros[i].first <= j) {
				matriz[j] = max(matriz[j], matriz[j - 3 * tesoros[i].first] + tesoros[i].second);
			}
		}
	}

	cout << matriz[T] << endl;*/
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int T, N;
	cin >> T >> N;
    if (!std::cin)
        return false;
    
	vector<pair<int, int>> tesoros;
	tesoros.push_back({ -1, -1 });

	for (size_t i = 0; i < N; i++){
		int p, cantidadOro;
		cin >> p >> cantidadOro;

		tesoros.push_back({ p, cantidadOro });
	}

	resuelve(tesoros, T);
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