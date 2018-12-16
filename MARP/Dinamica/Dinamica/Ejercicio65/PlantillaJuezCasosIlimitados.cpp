// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;

void resuelve(const vector<pair<string, string>>& rel, const int& P, int& grado) {
	int n = rel.size() - 1;
	Matriz<int> grados(P + 1, n + 1, 0);
	for (int i = 1;  i <= P; i++){
		grados[i][0] = 0;
		pair<string, string> anterior;
		for (int j = 1; j <= n; j++) {
			if (rel[j].first == anterior.first || rel[j].first == anterior.second) {
				grados[i][j] = grados[i][j - 1] + 1;
			}
			else {
				grados[i][j] = max(grados[i][j - 1], grados[i - 1][j]);
			}
			anterior = rel[j];
		}
	}
	grado = grados[P][n];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int P, R;
	cin >> P >> R;

    if (! std::cin)
        return false;

	vector<pair<string, string>> rel(R + 1);

	for (size_t i = 1; i <= R; i++){
		string p1, p2;
		cin >> p1 >> p2;
		rel[i] = { p1, p2 };
	}
	int grado = 0;
	resuelve(rel, P, grado);
	grado ? cout << grado : cout << "DESCONECTADA";
	cout << endl;
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