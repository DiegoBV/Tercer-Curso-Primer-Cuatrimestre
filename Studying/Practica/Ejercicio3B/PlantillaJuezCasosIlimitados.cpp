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
	vector<int> numFormas;

	void relax(AristaDirigida<int>& e) {
		int v = e.from(), w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			pq.update(w, distTo[w]);
			numFormas[w] = numFormas[v];
		}
		else if (distTo[w] == distTo[v] + e.valor()) {
			numFormas[w] += numFormas[v];
		}
	};

public:

	resuelve(const GrafoDirigidoValorado<int>& g): distTo(g.V(), numeric_limits<int>::max()),
		pq(g.V()), numFormas(g.V(), 0) {

		distTo[0] = 0;
		numFormas[0] = 1;
		pq.push(0, 0);

		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();

			for (AristaDirigida<int> e : g.ady(v)) {
				relax(e);
			}
		}

	};

	~resuelve() {};

	inline const int getSol() { return numFormas.back(); };
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
		int i1, i2, longi;
		cin >> i1 >> i2 >> longi;

		g.ponArista({ i1 - 1, i2 - 1, longi });
		g.ponArista({ i2 - 1, i1 - 1, longi });
	}

	resuelve sol(g);
    // escribir sol
	cout << sol.getSol() << endl;
    
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