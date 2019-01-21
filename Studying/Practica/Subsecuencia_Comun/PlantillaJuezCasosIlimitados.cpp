// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;

int subsecuencia(const string& palabra1, const string& palabra2) {
	int n = palabra1.size() - 1;
	int m = palabra2.size() - 1;

	Matriz<int> matriz(n + 2, m + 2, 0);

	for (int i = n; i >= 0; i--) {
		for (int j = m; j >= 0; j--) {
			if (palabra1[i] == palabra2[j]) {
				matriz[i][j] = matriz[i + 1][j + 1] + 1;
			}
			else {
				matriz[i][j] = max(matriz[i + 1][j], matriz[i][j + 1]);
			}
		}
	}

	vector<char> palabro(matriz[0][0]);
	int j = 0, i = 0, k0 = 0;

	while (i < palabra1.size() && j < palabra2.size()) {
		if (palabra1[i] == palabra2[j]) {
			palabro[k0] = palabra1[i];
			k0++;
			i++;
			j++;
		}
		else if(matriz[i][j] == matriz[i + 1][j]){
			i++;
		}
		else {
			j++;
		}
	}

	for (size_t i = 0; i < palabro.size(); i++){
		cout << palabro[i];
	}
	cout << " ";

	return matriz[0][0];
};

int subsecuencia2(const string& palabra1, const string& palabra2) {
	int n = palabra1.size() - 1;
	int m = palabra2.size() - 1;
	
	vector<int> matriz(m + 2, 0);
	for (int i = n; i >= 0; i--) {
		int aux = 0;
		for (int j = m; j >= 0; j--) {
			int temp = matriz[j];
			if (palabra1[i] == palabra2[j]) {
				matriz[j] = aux + 1;
			}
			else {
				matriz[j] = max(matriz[j], matriz[j + 1]);
			}
			aux = temp;
		}
	}

	return matriz[0];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	string palabra1, palabra2;
	cin >> palabra1 >> palabra2;
    if (!std::cin)
        return false;
	cout << subsecuencia(palabra1, palabra2) << endl;
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