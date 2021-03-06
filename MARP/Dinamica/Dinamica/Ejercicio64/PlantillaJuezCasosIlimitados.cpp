// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void pintaMatriz(Matriz<int>& matriz) {
	for (size_t i = 0; i < matriz.numfils(); i++){
		for (size_t j = 0; j < matriz.numcols(); j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
};

void patindromo(const string& palabra, string& palindromo) {
	int n = palabra.length();
	Matriz<int> matriz(n, n, 0);

	//rellenamos matriz
	matriz[n - 1][n - 1] = 1;
	for (int i = n - 2; i >= 0; i--) {
		matriz[i][i] = 1;
		for (int j = i + 1; j < n; j++) {
			if (palabra[i] == palabra[j]) {
				matriz[i][j] = matriz[i + 1][j - 1] + 2; //dos caracteres
			}
			else {
				matriz[i][j] = max(matriz[i][j - 1], matriz[i + 1][j]);
			}
		}
	}

	int longitud = matriz[0][n - 1];
	//pintaMatriz(matriz);

	vector<char> palin(longitud);
	int k0 = 0, k1 = palin.size() - 1;
	int j = n - 1;
	int i = 0;

	while (i <= j) {
		if (palabra[i] == palabra[j]) {
			palin[k0] = palin[k1] = palabra[i];
			k0++;
			k1--;
			j--;
			i++;
		}
		else if (matriz[i][j] == matriz[i + 1][j]) {
			i++;
		}
		else {
			j--;
		}
	}

	for (size_t i = 0; i < palin.size(); i++)
	{
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

    if (! std::cin)
        return false;
    
	string palindromo;

	patindromo(palabra, palindromo);
    
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