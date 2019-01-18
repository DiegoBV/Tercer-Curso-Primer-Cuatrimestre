// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;

int resuelve(const string& p1, const string& p2) {
	int n = p1.size() - 1;
	int m = p2.size() - 1;

	Matriz<int> matriz(n + 2, m + 2, 0);

	for (int i = n; i >= 0; i--) {
		for (int j = m; j >= 0; j--) {
			if (p1[i] == p2[j]) {
				matriz[i][j] = max(matriz[i + 1][j + 1] + 1, max(matriz[i + 1][j], matriz[i][j + 1]));
			}
			else {
				matriz[i][j] = max(matriz[i + 1][j], matriz[i][j + 1]);
			}
		}
	}

	vector<char> palabra(matriz[0][0]);

	int k0 = 0, k1 = palabra.size() - 1;
	int j = 0, i = 0;

	while (i < p1.size() && j < p2.size()) {
		if (p1[i] == p2[j]) {
			palabra[k0] = p1[i];
			k0++;
			i++;
			j++;
		}
		else if (matriz[i][j] == matriz[i + 1][j]) {
			i++;
		}
		else {
			j++;
		}
	}

	for (size_t i = 0; i < palabra.size(); i++)
	{
		cout << palabra[i];
	}

	cout << endl;

	return matriz[0][0];
};

int resuelve2(const string& p1, const string& p2) {
	int n = p1.size() - 1;
	int m = p2.size() - 1;

	vector<int> matriz(m + 2, 0);

	for (int i = n; i >= 0; i--) {
		int aux = 0;
		for (int j = m; j >= 0; j--) {
			int temp_ = matriz[j];
			if (p1[i] == p2[j]) {
				matriz[j] = max(matriz[j + 1], max(matriz[j], aux + 1));
			}
			else {
				matriz[j] = max(matriz[j], matriz[j + 1]);
			}
			aux = temp_;
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
    
	cout << resuelve(palabra1, palabra2) << endl;
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