// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
using namespace std;

class puede_pasar {
private:
	queue<Arista<int>> camino;
	bool puede_pasar_;

public:
	puede_pasar(const GrafoValorado<int>& g, int orig, int des, int anchura) : puede_pasar_(false) {
		ConjuntosDisjuntos union_(g.V());	
		queue<int> vertices;
		vertices.push(orig);

		while (!vertices.empty() && camino.size() < g.V() - 1 && !puede_pasar_) {  //no hace falta ordenarlos por minimos, no queremos saber el camino minimo
			int vertice = vertices.front();
			vertices.pop();

			for (Arista<int> e : g.ady(vertice)) {
				if (!union_.unidos(vertice, e.otro(vertice))) {
					if (e.valor() >= anchura) { //el camion puede pasar
						camino.push(e);
						vertices.push(e.otro(vertice));
						union_.unir(vertice, e.otro(vertice));
						if (e.otro(vertice) == des) {
							puede_pasar_ = true;
						}
					}
				}
			}
		}
	};

	bool puede_() const { return puede_pasar_; };

};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int V, E;
	cin >> V >> E;

    if (! std::cin)
        return false;
	GrafoValorado<int> g(V);

	for (size_t i = 0; i < E; i++)
	{
		int a, b, anchuraMax;
		cin >> a >> b >> anchuraMax;
		g.ponArista({ (a - 1), (b - 1), anchuraMax });
	}

	int K;
	cin >> K;

	for (size_t i = 0; i < K; i++)
	{
		int orig, dest, anch;
		cin >> orig >> dest >> anch;
		puede_pasar sol(g, orig - 1, dest - 1, anch);
		sol.puede_() ? cout << "SI" : cout << "NO";
		cout << endl;
	}
    
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