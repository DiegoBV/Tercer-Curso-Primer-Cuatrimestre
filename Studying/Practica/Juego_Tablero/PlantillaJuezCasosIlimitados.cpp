// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

bool esValida(Matriz<int>& casillas, const int i, const int j) {
	return (i >= 0 && i < casillas.numfils() && j >= 0 && j < casillas[i].size());
};

int resuelve(const vector<vector<int>>& tablero, int& columna) {
	int n = tablero.size() - 1;
	Matriz<int> matriz(n + 1, n + 1, 0);

	for (int i = n; i > 0; i--) {
		for (int j = 1; j <= n; j++) {
			int vert = 0, der = 0, izq = 0;
			if (esValida(matriz, i + 1, j)) {
				vert = matriz[i + 1][j];
			}
			if (esValida(matriz, i + 1, j - 1)) {
				izq = matriz[i + 1][j - 1];
			}
			if (esValida(matriz, i + 1, j + 1)) {
				der = matriz[i + 1][j + 1];
			}

			matriz[i][j] = max(max(vert + tablero[i][j], der + tablero[i][j]), izq + tablero[i][j]);
		}
	}

	int max = -1;
	for (size_t i = 0; i < matriz[1].size(); i++){
		if (matriz[1][i] > max) {
			max = matriz[1][i];
			columna = i;
		}
	}
	return max;
};

void resuelve2(vector<vector<int>>& casillas, int& puntuacion, int& pos) {

	int n = casillas.size() - 1;

	Matriz<int> mov(n + 1, n + 1, 0);

	//rellenamos
	for (size_t i = 1; i <= n; i++) {
		mov[i][0] = 0;
		for (size_t j = 1; j <= n; j++) {
				int d_izq = 0, vert = 0, d_der = 0;
				if (esValida(mov, i - 1, j)) {
					vert = mov[i - 1][j];
				}

				if (esValida(mov, i - 1, j - 1)) {
					d_izq = mov[i - 1][j - 1];
				}

				if (esValida(mov, i - 1, j + 1)) {
					d_der = mov[i - 1][j + 1];
				}

				mov[i][j] = max(max(vert + casillas[i][j], d_izq + casillas[i][j]),
					d_der + casillas[i][j]);
			

			/*mov[i][j] = max(max(mov[j][i - 1] + casillas[casillas.size() - (i - 1)][casillas.size() - j],
			mov[j - 1][i - 1] + casillas[casillas.size() - (i - 1)][casillas.size() - (j - 1)]), mov[j + 1][i - 1]);*/
		}
	}

	int max = -1;
	for (size_t i = 0; i < mov[n].size(); i++)
	{
		if (mov[n][i] > max) {
			max = mov[n][i];
			pos = i;
		}
	}
	puntuacion = mov[n][pos];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (! std::cin)
        return false;
	vector<vector<int>> tablero(N + 1, vector<int>(N + 1));
	for (size_t i = 1; i <= N; i++){
		for (size_t j = 1; j <= N; j++) {
			int el;
			cin >> el;

			tablero[i][j] = el;
		}
	}
   
	int p = 0, columna = 0;
	resuelve2(tablero, p, columna);
	// escribir sol
	cout << p << " " << columna << endl;
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