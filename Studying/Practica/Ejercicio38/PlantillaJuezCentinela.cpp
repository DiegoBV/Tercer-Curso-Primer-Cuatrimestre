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

	void relax(AristaDirigida<int>& e) {
		int v = e.from(), w = e.to();

		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			pq.update(w, distTo[w]);
		}
	}

public:
	resuelve(const GrafoDirigidoValorado<int>& g): 
		distTo(g.V(), numeric_limits<int>::max()), pq(g.V()) {

		distTo[0] = 0;

		pq.push(0, 0);

		while (!pq.empty()){
			int v = pq.top().elem;
			pq.pop();

			for (AristaDirigida<int> e : g.ady(v)) {
				relax(e);
			}
		}
	};

	~resuelve() {};

	inline const int getSol() { return distTo.back(); };
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	vector<int> tiempos_carga;
	GrafoDirigidoValorado<int> g(N);
	for (size_t i = 0; i < N; i++){
		int t;
		cin >> t;

		tiempos_carga.push_back(t);
	}

	int M;
	cin >> M;
	for (size_t i = 0; i < M; i++){
		int ori, dest, time;
		cin >> ori >> dest >> time;

		g.ponArista({ ori - 1, dest - 1, time + tiempos_carga[ori - 1] });
	}
    
	resuelve sol(g);
    // escribir sol
	sol.getSol() == numeric_limits<int>::max() ? cout << "IMPOSIBLE" << endl : 
		cout << sol.getSol() + tiempos_carga.back() << endl;
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
