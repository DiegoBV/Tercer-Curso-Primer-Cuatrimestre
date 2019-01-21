// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

int gorras(PriorityQueue<int>& pQueue) {
	int numGorras = 0;

	while (pQueue.size() != 1){
		int contrincante1 = pQueue.top();
		pQueue.pop();

		int contrincante2 = pQueue.top();
		pQueue.pop();

		int nuevoEquipo = contrincante1 + contrincante2;
		pQueue.push(nuevoEquipo);

		numGorras += nuevoEquipo;
	}

	return numGorras;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;
	PriorityQueue<int> pQueue;
	for (size_t i = 0; i < N; i++){
		int seguidores;
		cin >> seguidores;

		pQueue.push(seguidores);
	}
    
	cout << gorras(pQueue) << endl;
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
