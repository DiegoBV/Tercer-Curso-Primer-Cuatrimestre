// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void subsecuencia(const string& first, const string& second, int& length) {

	int n = first.length() - 1;
	int m = second.length() - 1;

	Matriz<int> matriz(n + 1, m + 1, 0);

	//rellenamos matriz
	for (size_t i = 1; i <= n; i++){
		for (size_t j = 1; j <= m; j++) {

			if (first[i] == second[j]) {
				matriz[i][j] = max(matriz[i - 1][j - 1] + 1, max(matriz[i - 1][j], matriz[i][j - 1]));
			}
			else {
				matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
			}
		}
	}

	length = matriz[n][m];
};

void subsecuencia2(const string& first, const string& second, int& length) {
	
	int n = first.length() - 1;
	int m = second.length() - 1;

	vector<int> matriz(m + 1);


	//rellenar matriz
	for (size_t i = 1; i <= n; i++){
		int aux = 0;
		for (size_t j = 1; j <= m; j++){

			int temp_ = matriz[j]; //??

			if (first[i] == second[j]) {	
				matriz[j] = max(aux + 1, max(matriz[j], matriz[j - 1]));
			}
			else {
				matriz[j] = max(matriz[j], matriz[j - 1]);
			}
			aux = temp_;
		}
	}

	length = matriz.back();
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	string palabra1, palabra2;

	cin >> palabra1 >> palabra2;

    if (! std::cin)
        return false;
    
	int length = 0;

	palabra1.insert(palabra1.begin(), '?');
	palabra2.insert(palabra2.begin(), '?');

	subsecuencia2(palabra1, palabra2, length);
    // escribir sol
    
	cout << length << endl;
    
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