// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void representa(const vector<vector<int>>& tablero) {
	for (size_t i = 0; i < tablero.size(); i++) {
		for (size_t j = 0; j < tablero[i].size(); j++) {
			cout << tablero[i][j] << " ";
		}
		cout << endl;
	}
};

bool esCorrecta(const Matriz<int>& m, const int& i, const int& j) {
	return (i >= 0 && i < m.numfils() && j >= 0 && j < m.numcols());
};

int resuelve(const vector<vector<int>>& tablero, int& colInicial) {
	int n = tablero.size() - 1;
	Matriz<int> matriz(n + 1, n + 1, 0);


	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= n; j++) {
			int v = 0, diag_izq = 0, diag_der = 0;

			if (esCorrecta(matriz, i - 1, j)) {
				v = matriz[i - 1][j];
			}
			if (esCorrecta(matriz, i - 1, j - 1)) {
				diag_izq = matriz[i - 1][j - 1];
			}
			if (esCorrecta(matriz, i - 1, j + 1)) {
				diag_der = matriz[i - 1][j + 1];
			}

			matriz[i][j] = max(v + tablero[i][j], max(diag_izq + tablero[i][j],
				diag_der + tablero[i][j]));
		}
	}

	int max = -1;
	for (size_t i = 0; i < matriz[n].size(); i++){
		if (matriz[n][i] > max) {
			max = matriz[n][i];
			colInicial = i;
		}
	}

	return matriz[n][colInicial];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (!std::cin)
        return false;

	vector<vector<int>> tablero(N + 1, vector<int>(N + 1));
	for (size_t i = 1; i <= N; i++){
		for (size_t j = 1; j <= N; j++){
			int cas;
			cin >> cas;

			tablero[i][j] = cas;
		}
	}

	int col = 0;

	cout << resuelve(tablero, col) << " " << col << endl;
	/*representa(tablero);
	cout << endl << endl << endl;*/
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