// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <limits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

class resuelve {
private:
	vector<int> distTo;
	vector<int> distToInv;
	IndexPQ<int> pQueue;
	IndexPQ<int> pQueueInv;
	int esfuerzo_minimo;
	bool es_posible;

	void relax(AristaDirigida<int> a, vector<int>& dist, IndexPQ<int>& queue) {
		int v = a.from(), w = a.to();

		if (dist[w] > dist[v] + a.valor())
		{
			dist[w] = dist[v] + a.valor();
			queue.update(w, dist[w]);
		}
	}

	void djistra(const GrafoDirigidoValorado<int>& g, int ori, vector<int>& dist, IndexPQ<int>& pQ) {
		for (size_t i = 0; i < dist.size(); i++) {
			dist[i] = numeric_limits<int>::max();
		}
		dist[ori] = 0; // casa inicial
		pQ.push(ori, 0);

		while (!pQ.empty()) {
			int vertice = pQ.top().elem;
			pQ.pop();

			for (AristaDirigida<int> a : g.ady(vertice)) {
				relax(a, dist, pQ);
			}
		}
	}

public:
	resuelve(const GrafoDirigidoValorado<int>& g, queue<int>& cola_paquetes, const int ORIGEN) : distTo(g.V()), pQueue(g.V()), distToInv(g.V()),pQueueInv(g.V()), esfuerzo_minimo(0), es_posible(true) {
		djistra(g, ORIGEN, distTo, pQueue);
		GrafoDirigidoValorado<int> gInverso = g.inverso();
		djistra(gInverso, ORIGEN, distToInv, pQueueInv);

		while (!cola_paquetes.empty() && esPosible()) {
			int v = cola_paquetes.front();
			cola_paquetes.pop();

			if (distTo[v] != numeric_limits<int>::max() && distToInv[v] != numeric_limits<int>::max()) {
				esfuerzo_minimo += distTo[v];
				esfuerzo_minimo += distToInv[v];
			}
			else {
				es_posible = false;
			}
		}
	};

	inline bool esPosible() const { return es_posible; };
	inline int esfuerzo() const { return esfuerzo_minimo; };
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, C;
	cin >> N >> C;

    if (! std::cin)
        return false;

	GrafoDirigidoValorado<int> g(N);

	for (size_t i = 0; i < C; i++){
		int origen, destino, esfuerzo;
		cin >> origen >> destino >> esfuerzo;

		g.ponArista({ origen - 1, destino - 1, esfuerzo });
	}

	int O, P;
	cin >> O >> P;
	queue<int> cola_paquetes;

	for (size_t i = 0; i < P; i++){
		int numCasa;
		cin >> numCasa;

		cola_paquetes.push(numCasa - 1);
	}
	resuelve sol(g, cola_paquetes, O - 1);
    // escribir sol
	sol.esPosible() ? cout << sol.esfuerzo() << endl : cout << "Imposible" << endl;
    
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