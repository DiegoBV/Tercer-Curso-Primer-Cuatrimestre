// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;

void pintaMatriz(Matriz<int>& matriz) {
	for (size_t i = 0; i < matriz.numfils(); i++) {
		for (size_t j = 0; j < matriz.numcols(); j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
};

void resuelve(const string& palabra) {
	int n = palabra.size() - 1;
	Matriz<int> matriz(n + 1, n + 1, 0);

	//diagonal
	for (int i = 0; i <= n; i++) {
		matriz[i][i] = 1;
	}

	for (int i = n; i >= 0; i--) {
		for (int j = i + 1; j <= n; j++) {
			if (palabra[i] == palabra[j]) {
				matriz[i][j] = matriz[i + 1][j - 1] + 2;
			}
			else {
				matriz[i][j] = max(matriz[i + 1][j], matriz[i][j - 1]);
			}
		}
	}

	//cout << matriz[0][n] << endl;

	//reconstruccion
	int j = n;
	int i = 0;
	int k0 = 0;
	vector<char> palin(matriz[0][n]);
	int k1 = palin.size() - 1;

	while (i <= j) {
		if (palabra[i] == palabra[j]) {
			palin[k0] = palin[k1] = palabra[i];
			i++;
			j--;
			k0++;
			k1--;
		}
		else if (matriz[i][j] == matriz[i + 1][j]) {
			i++;
		}
		else {
			j--;
		}
	}

	for (int i = 0; i < palin.size(); i++) {
		cout << palin[i];
	}

	cout << endl;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	string palabra;
	cin >> palabra;
    if (!std::cin)
        return false;
    
	resuelve(palabra);
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