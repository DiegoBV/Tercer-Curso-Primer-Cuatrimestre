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

	Tarea() {};
	Tarea(int c, int f, int p = -1) : tc(c), tf(f), p(p) {};
};

bool operator<(const Tarea& t1, const Tarea& t2) { return t1.tc < t2.tc; };

bool resuelve(PriorityQueue<Tarea>& pQueue, const int T) {
	bool hay_conflicto = false;
	bool time_is_over = false;

	Tarea t = Tarea(-1, -1, -1);

	while (!pQueue.empty() && !time_is_over && !hay_conflicto) {
		Tarea t2 = pQueue.top();
		pQueue.pop();

		if (t2.tc >= T) {
			time_is_over = true;
		}
		else if(t2.tc < t.tf) {
			hay_conflicto = true;
		}

		if (t2.p != -1) {
			pQueue.push({ t2.tc + t2.p, t2.tf + t2.p, t2.p });
		}

		t = t2;
	}

	return hay_conflicto;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, M, T;
	cin >> N >> M >> T;

    if (! std::cin)
        return false;

	PriorityQueue<Tarea> pQueue;
	for (size_t i = 0; i < N; i++){
		int tc, tf;
		cin >> tc >> tf;

		pQueue.push({tc, tf});
	}

	for (size_t i = 0; i < M; i++){
		int tc, tf, p;
		cin >> tc >> tf >> p;

		pQueue.push({ tc, tf, p });
	}

    // escribir sol
	resuelve(pQueue, T) ? cout << "SI" << endl : cout << "NO" << endl;
    
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