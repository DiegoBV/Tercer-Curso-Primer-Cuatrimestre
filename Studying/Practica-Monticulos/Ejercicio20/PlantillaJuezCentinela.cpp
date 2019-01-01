// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

int resuelve(PriorityQueue<long long int>& pQueue) {
	int esfuerzo = 0;

	int sumando = pQueue.top();
	pQueue.pop();

	while (!pQueue.empty()) {
		int suma = 0;
		suma = sumando + pQueue.top();
		esfuerzo += suma;
		pQueue.pop();
		pQueue.push(suma);

		if (pQueue.size() == 1) {
			pQueue.pop();
		}
		else {
			sumando = pQueue.top();
			pQueue.pop();
		}
	}

	return esfuerzo;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
	PriorityQueue<long long int> pQueue;

	for (size_t i = 0; i < N; i++){
		long long int sumando;
		cin >> sumando;
		pQueue.push(sumando);
	}
    
    // escribir sol
	cout << resuelve(pQueue) << endl;
    
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
