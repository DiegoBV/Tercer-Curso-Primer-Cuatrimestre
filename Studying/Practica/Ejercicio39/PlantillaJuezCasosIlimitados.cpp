// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

class resuelve
{
private:
	vector<int> distTo;
	IndexPQ<int> pq;
	int esfuerzo_total;
	bool se_puede;

	void relax(AristaDirigida<int>& e) {
		int v = e.from(), w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			pq.update(w, distTo[w]);
		}
	};

	void Dijkstra(const GrafoDirigidoValorado<int>& g, const int O) {

		distTo[O] = 0;
		pq.push(O, 0);

		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (AristaDirigida<int> e : g.ady(v)) {
				relax(e);
			}
		}

	};

public:

	resuelve(const GrafoDirigidoValorado<int>& g, const int O, const vector<int>& destinos): distTo(g.V(), numeric_limits<int>::max()),
		pq(g.V()), esfuerzo_total(0), se_puede(true) {

		Dijkstra(g, O);
		for (size_t i = 0; i < destinos.size() && se_puede; i++){
			if (distTo[destinos[i]] != numeric_limits<int>::max()) {
				esfuerzo_total += distTo[destinos[i]];
			}
			else {
				se_puede = false;
			}
		}

		GrafoDirigidoValorado<int> g_inverso = g.inverso();

		pq = IndexPQ<int>(g.V());
		distTo = vector<int>(g.V(), numeric_limits<int>::max());

		Dijkstra(g_inverso, O);
		for (size_t i = 0; i < destinos.size() && se_puede; i++) {
			if (distTo[destinos[i]] != numeric_limits<int>::max()) {
				esfuerzo_total += distTo[destinos[i]];
			}
			else {
				se_puede = false;
			}
		}
	};

	~resuelve() {};

	inline const bool sePuede() { return se_puede; };
	inline const int esfuerzo() { return esfuerzo_total; };
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, C;
	cin >> N >> C;

    if (!std::cin)
        return false;

	GrafoDirigidoValorado<int> g(N);
	for (size_t i = 0; i < C; i++){
		int origen, destino, esfuerzo;
		cin >> origen >> destino >> esfuerzo;

		g.ponArista({ origen - 1, destino - 1, esfuerzo });
	}

	int O, P;
	cin >> O >> P;
	vector<int> destinos;
	for (size_t i = 0; i < P; i++){
		int dest;
		cin >> dest;

		destinos.push_back(dest - 1);
	}
 
	resuelve sol(g, O - 1, destinos);
    // escribir sol
	sol.sePuede() ? cout << sol.esfuerzo() << endl : cout << "Imposible" << endl;
    
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