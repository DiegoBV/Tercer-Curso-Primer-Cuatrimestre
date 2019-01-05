// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "Grafo.h"

using namespace std;

class bipartito
{
private:
	vector<bool> marcados;
	bool es_bipartito;
	vector<int> distTo;

	void comprueba_condicion(const int v, const int w) {
		if (distTo[v] % 2 == 0 && distTo[w] % 2 == 0) {
			es_bipartito = false;
		}
		else if (distTo[v] % 2 != 0 && distTo[w] % 2 != 0) {
			es_bipartito = false;
		}
	};

	void bfs(const Grafo& g, const int V) {
		queue<int> v_queue;
		v_queue.push(V);
		marcados[V] = true;

		while (!v_queue.empty() && es_bipartito) {
			int ver = v_queue.front();
			v_queue.pop();

			for (int w : g.ady(ver)) {
				if (!marcados[w]) {
					marcados[w] = true;
					v_queue.push(w);
					distTo[w] = distTo[ver] + 1;
				}
				else {
					comprueba_condicion(ver, w);
				}
			}
		}
	};

public:
	bipartito(const Grafo& g): marcados(g.V(), false), distTo(g.V(), 0), es_bipartito(true){
		for (int i = 0; i < g.V() && es_bipartito; i++) {
			if (!marcados[i]) {
				bfs(g, i);
			}
		}
	};

	~bipartito() {};

	inline bool const esBipartito() { return es_bipartito; };
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, E;
	cin >> N >> E;

    if (!std::cin)
        return false;
   
	Grafo g(N);
	for (size_t i = 0; i < E; i++){
		int a, b;
		cin >> a >> b;

		g.ponArista(a, b);
	}
    
	bipartito sol(g);
    // escribir sol
	sol.esBipartito() ? cout << "SI" : cout << "NO";
	cout << endl;
    
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