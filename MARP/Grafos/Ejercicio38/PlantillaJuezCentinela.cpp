// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

/*struct PaginaWeb
{
	int numeroPagina_;
	int tiempoCarga_;
	PaginaWeb() : numeroPagina_(-1), tiempoCarga_(-1) {};
	PaginaWeb(int n, int t) : numeroPagina_(n), tiempoCarga_(t) {};
};*/
class resuelve {
private:
	vector<int> distTo;
	IndexPQ<int> pQueue;
	bool existe_camino;

	void relax(AristaDirigida<int>& e) {
		int v = e.from();
		int w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			pQueue.update(w, distTo[w]);
		}
	}

public:
	resuelve(GrafoDirigidoValorado<int>& g/*, const vector<int>& tiemposCarga*/): distTo(g.V()), pQueue(g.V()), existe_camino(false) {
		for (size_t i = 0; i < distTo.size(); i++){
			distTo[i] = numeric_limits<int>::max();
		}
		distTo[0] = 0; //pagina inicial
		pQueue.push(0, 0);

		while (!pQueue.empty()) {
			int v = pQueue.top().elem;
			pQueue.pop();
			for (AristaDirigida<int> e : g.ady(v)) {
				relax(e);
			}
		}

		if (distTo.back() != numeric_limits<int>::max()) {
			existe_camino = true;
		}
	};

	inline bool existePath() const { return existe_camino; };
	inline int getDist() const { return distTo.back(); };
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;
	GrafoDirigidoValorado<int> g(N);
	vector<int> tiemposCarga;

	for (size_t i = 0; i < N; i++){
		int t;
		cin >> t;
		tiemposCarga.push_back(t);
	}

	int M;
	cin >> M;

	for (size_t i = 0; i < M; i++){
		int pagActual, pagDest, tiempo;
		cin >> pagActual >> pagDest >> tiempo;
		g.ponArista(AristaDirigida<int>{ pagActual - 1, pagDest - 1, tiempo + tiemposCarga[pagActual - 1] }); //mm??
	}

	resuelve sol(g);
    // escribir sol
	sol.existePath() ? cout << sol.getDist() + tiemposCarga[N - 1] << endl : cout << "IMPOSIBLE" << endl;
	
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
