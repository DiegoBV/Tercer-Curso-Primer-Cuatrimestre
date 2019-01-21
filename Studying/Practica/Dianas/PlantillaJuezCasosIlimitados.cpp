// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void resuelve(const vector<int>& sectores, const int& P) {
	int n = sectores.size() - 1;
	Matriz<int> matriz(n + 1, P + 1, 1E9);

	matriz[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= P; j++) {
			if (sectores[i] > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - sectores[i]] + 1);
			}
		}
	}

	if (matriz[n][P] != 1E9) {
		cout << matriz[n][P] << ":" << " ";
		int i = n; int j = P;
		while (j > 0) { 
			if (sectores[i] <= j && matriz[i][j] == matriz[i][j - sectores[i]] + 1) {
				cout << sectores[i] << " ";
				j = j - sectores[i];
			}
			else {
				--i;
			}
		}

		cout << endl;
	}
	else {
		cout << "Imposible" << endl;
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int VALOR, S;
	cin >> VALOR >> S;
    if (! std::cin)
        return false;
	vector<int> sectores(S + 1);
	for (size_t i = 1; i <= S; i++){
		int p;
		cin >> p;

		sectores[i] = p;
	}
    
	resuelve(sectores, VALOR);
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