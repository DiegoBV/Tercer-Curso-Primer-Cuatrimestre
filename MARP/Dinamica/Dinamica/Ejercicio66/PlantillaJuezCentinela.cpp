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
};

void cortes_(vector<int>& cortes, const int& L, int& esfuerzo) {
	int n = L;

	Matriz<int> matriz(L + 1, L + 1, 0);

	for (size_t i = 0; i <= n ; i++)
	{
		matriz[i][i] = 2 * i;
	}
	//

	for (int d = 1; d <= L; d++) {
		for (int i = 1; i <= L - d; i++) {
			int izq;
			//matriz[i][i + d] = min(matriz[i][i + d - 1] + 2*(i + d), matriz[i - 1][i + d] + 2 * (i+d));
		}
	}
	esfuerzo = matriz[0][L];
	pintaMatriz(matriz);
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int L, N;
	cin >> L >> N;

    if (L == 0 && N == 0)
        return false;
    
	vector<int> cortes(N + 1);
	for (size_t i = 1; i <= N; i++)
	{
		int corte;
		cin >> corte;

		cortes[i] = corte;
	}
	int esfuerzo = 0;
	cortes_(cortes, L, esfuerzo);
    // escribir sol
	cout << esfuerzo << endl;
    
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
