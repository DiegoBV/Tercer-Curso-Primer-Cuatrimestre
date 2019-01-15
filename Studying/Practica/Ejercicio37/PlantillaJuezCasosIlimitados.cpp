// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

using namespace std;

class resuelve
{
private:
	int coste_total;
public:
	resuelve(const GrafoValorado<int>& g, PriorityQueue<Arista<int>>& pq): coste_total(0) {
		ConjuntosDisjuntos cjto(g.V());

		while (!pq.empty() && cjto.num_cjtos() != 1) {
			Arista<int> e = pq.top();
			pq.pop();
			int v = e.uno(), w = e.otro(v);

			if (!cjto.unidos(v, w)) {
				cjto.unir(v, w);
				coste_total += e.valor();
			}
		}

		if (cjto.num_cjtos() != 1) {
			coste_total = -1;
		}
	};

	~resuelve() {};

	inline const int getSol() { return coste_total; };

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
		int i1, i2, coste;
		cin >> i1 >> i2 >> coste;

		g.ponArista({ i1 - 1, i2 - 1, coste });
		pq.push({ i1 - 1, i2 - 1, coste });
	}
	resuelve sol(g, pq);

	sol.getSol() != -1 ? cout << sol.getSol() << endl : cout << "No hay puentes suficientes" << endl;
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