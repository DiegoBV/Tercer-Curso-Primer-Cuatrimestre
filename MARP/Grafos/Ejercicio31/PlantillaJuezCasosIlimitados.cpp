// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "Grafo.h"

using namespace std;

class es_bipartito {
private:
	vector<bool> marcados;
	vector<int> recorrido;
	vector<int> distToOrigin;
	bool es_bipartito_ = true;

	void compruebaCondicion(const int& padre, const int& hijo) {
		if (distToOrigin[padre] % 2 == 0) { //distancia del padre es par
			if (distToOrigin[hijo] % 2 == 0) { //si la distancia del hijo tambien es par, no puede ser bipartito
				es_bipartito_ = false;
			}
		}
		else { //distancia del padre es impar
			if (distToOrigin[hijo] % 2 != 0) { //si la distancia del hijo tambien es impar, no puede ser bipartito
				es_bipartito_ = false;
			}
		}
	};

	void bfs(const Grafo& g, const int& V) {
		queue<int> q;
		q.push(V);
		marcados[V] = true;

		while (!q.empty() && es_bipartito_) {
			int padre = q.front();
			q.pop();
			recorrido.push_back(padre);

			for (int hijo : g.ady(padre)) {
				if (!marcados[hijo]) { //si su "hijo" no está marcado, lo marca y lo añade a la cola
					marcados[hijo] = true;
					q.push(hijo);
					distToOrigin[hijo] = distToOrigin[padre] + 1; //la distancia al origen es la distancia del padre + 1
				}
				else { //si ya esta marcado, significa que la distancia con el vertice no puede ser par o impar dependiendo de su distancia
					compruebaCondicion(padre, hijo);
				}
			}
			
		}

	};
public:
	es_bipartito() {};
	es_bipartito(const Grafo& g, const int& V) : marcados(g.V(), false), distToOrigin(g.V(), 0) {
		for (int i = 0; i < g.V(); i++) {
			if (!marcados[i]) {
				bfs(g, i);
			}
		}
	};

	void representa_niveles() {
		for (int i : recorrido) {
			cout << i << " ";
		}

		cout << endl;
	};

	void representa_distancias() {
		for (int i : distToOrigin) {
			cout << i << " ";
		}

		cout << endl;
	};

	void respuesta() {
		es_bipartito_ ? cout << "SI"<< endl : cout << "NO" << endl;
	}
};



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int num, aristas;
	cin >> num >> aristas;

    if (! std::cin)
        return false;

	Grafo g(num);
	for (int i = 0; i < aristas; i++) {
		int e1, e2;
		cin >> e1 >> e2;

		g.ponArista(e1, e2);
	}
    
	es_bipartito sol(g, 0);
    // escribir sol
	sol.respuesta();
    
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