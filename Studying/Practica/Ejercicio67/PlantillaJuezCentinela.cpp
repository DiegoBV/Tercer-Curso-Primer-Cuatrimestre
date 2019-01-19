// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void pintaMatriz(Matriz<int>& matriz) {
	for (size_t i = 0; i < matriz.numfils(); i++) {
		for (size_t j = 0; j < matriz.numcols(); j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl << endl << endl;
};

void resuelve(const vector<int>& cubos) {
	int n = cubos.size() - 1;
	Matriz<int> matriz(n + 1, n + 1, 0);

	for (int i = 1; i <= n; i++) {
		matriz[i][i] = cubos[i];
		if (i + 1 <= n) {
			matriz[i][i + 1] = max(cubos[i], cubos[i + 1]);
		}
	}

	//pintaMatriz(matriz);

	for(int i = n; i > 0; i--) {
		for (int j = i + 2; j <= n; j++) {
			int izq = (cubos[i + 1] > cubos[j]) ? matriz[i + 2][j] : matriz[i + 1][j - 1];
			int der = (cubos[i] > cubos[j - 1]) ? matriz[i + 1][j - 1] : matriz[i][j - 2];

			matriz[i][j] = max(izq + cubos[i], der + cubos[j]);
		}
	}

	cout << matriz[1][n] << endl;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;
	vector<int> cubos(N + 1);
	for (size_t i = 1; i <= N; i++){
		int elem;
		cin >> elem;

		cubos[i] = elem;
	}

	resuelve(cubos);
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
