// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void patindromo(const string& palabra, string& palindromo) {
	int n = palabra.length();
	Matriz<int> matriz(n, n, 0);


	/*int i = 0; int j = n;

	while (i != j || j < i) {
		if (j == i) { //palabra de un solo caracter
			matriz[i][j] = 1;
		}
		else if (j < i) { //palabra vacia
			matriz[i][j] = 0;
		}
		else if (palabra[i] == palabra[j]) {
			matriz[i][j] = matriz[i + 1][j - 1] + 2; //dos caracteres
		}
		else {
			matriz[i][j] = max(matriz[i + 1][j], matriz[i][j - 1]);
		}
	}*/
	//rellenamos matriz
	matriz[n - 1][n - 1] = 1;
	for (int i = n - 2; i >= 0; i--) {
		matriz[i][i] = 1;
		for (int j = i + 1; j < n; j++) {

			if (palabra[i] == palabra[j]) {
				matriz[i][j] = matriz[i - 1][j + 1] + 2; //dos caracteres
			}
			else {
				matriz[i][j] = max(matriz[i][j - 1], matriz[i + 1][j]);
			}
		}
	}

	int longitud = matriz[0][n - 1];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	string palabra;
	cin >> palabra;

    if (! std::cin)
        return false;
    
	string palindromo = palabra;

	patindromo(palabra, palindromo);
    // escribir sol
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