// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;

void resuelve(const string& palabra) {
	int n = palabra.size() - 1;
	Matriz<int> matriz(n + 1, n + 1, 1E9);

	for (int i = 0; i <= n; i++) {
		matriz[i][i] = 0;
	}

	for (int i = n; i >= 0; i--) {
		for (int j = i + 1; j <= n; j++) {
			if (palabra[i] == palabra[j]) {
				matriz[i][j] = matriz[i + 1][j - 1];
			}
			else {
				matriz[i][j] = min(matriz[i + 1][j] + 1, matriz[i][j - 1] + 1);
			}
		}
	}

	cout << matriz[0][n] << endl;

	//reconstruccion
	vector<char> palin(palabra.size() + matriz[0][n]);
	int k0 = 0, k1 = palin.size() - 1;
	int i = 0, j = n;
	while (i <= j) {
		if (palabra[i] == palabra[j]) {
			palin[k0] = palin[k1] = palabra[i];
			k0++;
			k1--;
			i++;
			j--;
		}
		else if (matriz[i][j] == matriz[i + 1][j] + 1 && matriz[i][j] == matriz[i][j - 1] + 1) {
			if (palabra[i] > palabra[j]) {
				palin[k0] = palin[k1] = palabra[i];
				k1--;
				k0++;
				i++;
			}
			else {
				palin[k0] = palin[k1] = palabra[j];
				k1--;
				k0++;
				j--;
			}
		}
		else if (matriz[i][j] == matriz[i + 1][j] + 1){
			palin[k0] = palin[k1] = palabra[i];
			k1--;
			k0++;
			i++;
		}
		else {
			palin[k0] = palin[k1] = palabra[j];
			k1--;
			k0++;
			j--;
		}
	}

	for (size_t i = 0; i < palin.size(); i++)
	{
		cout << palin[i];
	}
	cout << endl;
};

void resuelve2(const string& palabra) {
	int n = palabra.size() - 1;
	vector<int> matriz(n + 1, 1E9);

	for (int i = n; i >= 0; i--) {
		int aux = 0;
		for (int j = 0; j <= n; j++) {
			int temp = matriz[j];
			if (palabra[i] == palabra[j]) {
				matriz[j] = aux;
			}
			else {
				if (j - 1 < 0) {
					matriz[j] = 0;
				}
				else {
					matriz[j] = min(matriz[j] + 1, matriz[j - 1] + 1);
				}
			}
			aux = temp;
		}
	}

	cout << matriz[n] << endl;
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