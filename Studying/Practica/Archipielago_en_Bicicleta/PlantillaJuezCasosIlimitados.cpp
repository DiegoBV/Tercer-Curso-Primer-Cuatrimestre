// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

class kruskal
{
private:
	int costeTotal;
	bool esPosible;

public:

	kruskal(const GrafoValorado<int>& g, PriorityQueue<Arista<int>>& pq): costeTotal(0), 
		esPosible(true) {
		ConjuntosDisjuntos uf(g.V());

		while (!pq.empty() && uf.num_cjtos() != 1) {
			Arista<int> e = pq.top();
			pq.pop();

			int v = e.uno(), w = e.otro(v);
			if (!uf.unidos(v, w)) {
				uf.unir(v, w);
				costeTotal += e.valor();
			}
		}

		if (uf.num_cjtos() != 1) {
			esPosible = false;
		}
	};

	~kruskal() {};

	inline const bool esPos() { return esPosible; };
	inline const int getSol() { return costeTotal; };
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int I, P;
	cin >> I >> P;
    if (!std::cin)
        return false;
	GrafoValorado<int> g(I);
	PriorityQueue<Arista<int>> pq;
	for (size_t i = 0; i < P; i++){
		int isla1, isla2, coste;
		cin >> isla1 >> isla2 >> coste;

		g.ponArista({ isla1 - 1, isla2 - 1, coste });
		pq.push({ isla1 - 1, isla2 - 1, coste });
	}

	kruskal sol(g, pq);
    // escribir sol
	sol.esPos() ? cout << sol.getSol() << endl : cout << "No hay puentes suficientes" << endl; 

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