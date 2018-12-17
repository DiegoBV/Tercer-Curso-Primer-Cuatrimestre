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

void patindromo(const string& palabra, string& palindromo, vector<bool> & cuales) {
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
	int ppo = 0;
	int fin = palin.size() - 1;
	int resto = n - 1;
	for (int i = 1; i <= n - 1; i++) {

		if (palabra[i] == palabra[resto]) {
			palin[ppo] = palabra[i];
			palin[fin] = palabra[resto];
			fin--;
			ppo++;
		}
		else if (matriz[i][resto] == matriz[i - 1][resto]) {
			palin[fin] = palabra[i];
			fin--;
		}
		else {
			palin[ppo] = palabra[resto];
			ppo++;
		}
		resto--;
		/*if (i != n - 1 && matriz[i][resto] == matriz[i + 1][resto] && matriz[i][resto] != 0) {
			//significa que no hemos venido por este camino
			cuales[i] = false;
		}
		else {
			//significa que hemos venido por aqui
			cuales[i] = true;
			resto--;
		}*/
	}
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
	vector<bool> cuales;

	patindromo(palabra, palindromo, cuales);
    // escribir sol
	for (int i = 0; i < cuales.size(); i++) {
		if (cuales[i]) palindromo.push_back(palabra[i]);
	}
	cout << palindromo << endl;
    
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