// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

struct Instrumentos
{
	float n, partituras, n_atril;

	Instrumentos() {};
	Instrumentos(int n) : n(n), partituras(1), n_atril(n) {};
};

bool operator<(const Instrumentos& i1, const Instrumentos& i2) {
	return i1.n_atril > i2.n_atril || (i1.n_atril == i2.n_atril
		&& i1.partituras < i2.partituras);
};

int resuelve(PriorityQueue<Instrumentos>& pQueue, const int P) {
	int partituras = P;
	partituras -= pQueue.size(); //le damos una a cada uno

	while (partituras > 0) {
		Instrumentos i = pQueue.top();
		pQueue.pop();

		i.partituras++;
		partituras--;
		i.n_atril =ceil( i.n / i.partituras);

		pQueue.push(i);
	}

	return pQueue.top().n_atril;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int P, N;
	cin >> P >> N;

    if (!std::cin)
        return false;
    
	PriorityQueue<Instrumentos> pQueue;
	for (size_t i = 0; i < N; i++){
		int musicos;
		cin >> musicos;

		pQueue.push({ musicos });
	}

    // escribir sol
	cout << resuelve(pQueue, P) << endl;
    
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