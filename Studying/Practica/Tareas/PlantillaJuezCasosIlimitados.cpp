// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct Tarea
{
	int tc, tf, p;

	Tarea(int tc, int tf, int p = -1) : tc(tc), tf(tf), p(p) {};
	Tarea() {};
};

bool operator<(const Tarea& t1, const Tarea& t2) { return t1.tc < t2.tc; };

bool resuelve(PriorityQueue<Tarea>& pQueue, const int& T) {
	bool conf = false;
	bool timeout = false;
	Tarea offset = pQueue.top();
	pQueue.pop();
	if (offset.p != -1) {
		pQueue.push({offset.tc + offset.p, offset.tf + offset.p, offset.p});
	}
	while (!pQueue.empty() && !conf && !timeout) {
		if(pQueue.top().tc >= T){
			timeout = true;
		}
		else {
			if (offset.tf > pQueue.top().tc) {
				conf = true;
			}
			else {
				offset = pQueue.top();
				pQueue.pop();
				if (offset.p != -1) {
					pQueue.push({ offset.tc + offset.p, offset.tf + offset.p, offset.p });
				}
			}
		}
	}

	return conf;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, M, T;
	cin >> N >> M >> T;
    if (!std::cin)
        return false;
	PriorityQueue<Tarea> pQueue;
	for (size_t i = 0; i < N; i++){
		int tc, tf;
		cin >> tc >> tf;
		pQueue.push({tc, tf});
	}
	for (size_t i = 0; i < M; i++) {
		int tc, tf, p;
		cin >> tc >> tf >> p;
		pQueue.push({ tc, tf, p });
	}
    
	resuelve(pQueue, T) ? cout << "SI" << endl : cout << "NO" << endl;
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