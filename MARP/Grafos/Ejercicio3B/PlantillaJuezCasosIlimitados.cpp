// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

class resuelve {
private:
	vector<int> distTo;
	IndexPQ<int> pq;
	vector<int> numeroFormas;
	int size;

	void relax(AristaDirigida<int>& a) {

		int v = a.from();
		int w = a.to();

		if (distTo[w] > distTo[v] + a.valor()) {
			distTo[w] = distTo[v] + a.valor();
			pq.update(w, distTo[w]);
			numeroFormas[w] = numeroFormas[v];
		}
		else if (distTo[w] == distTo[v] + a.valor()) { //otra forma de llegar a un vertice
			numeroFormas[w] += numeroFormas[v];
		}
	}
public:
	resuelve(const GrafoDirigidoValorado<int>& g) : 
		distTo(g.V(), numeric_limits<int>::max()), pq(g.V()), numeroFormas(g.V(), 0), size(g.V() - 1) {
		distTo[0] = 0;
		pq.push(0, 0);
		numeroFormas[0] = 1;

		while (!pq.empty()) {
			int vertice = pq.top().elem;
			pq.pop();

			for (AristaDirigida<int> a : g.ady(vertice)) {
				relax(a);
			}
		}
	};

	int getSol() const { return numeroFormas[size]; }
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
		int calle1, calle2, longitud;
		cin >> calle1 >> calle2 >> longitud;

		g.ponArista(AristaDirigida<int>(calle1 - 1, calle2 - 1, longitud));
		g.ponArista(AristaDirigida<int>(calle2 - 1, calle1 - 1, longitud));
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