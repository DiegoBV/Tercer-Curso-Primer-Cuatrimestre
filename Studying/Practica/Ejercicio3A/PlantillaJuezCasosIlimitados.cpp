// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
#include "Grafo.h"

using namespace std;

class prepara_fiesta
{
private:
	vector<bool> marcados;
	vector<int> distTo;
	int numero_maximo;

	void bfs(const Grafo& g, const int V) {
		queue<int> q;
		q.push(V);
		marcados[V] = true;
		distTo[V] = 0;
		int num_amigos = 1, num_enemigos = 0;

		while (!q.empty()) {
			int verticePadre = q.front();
			q.pop();

			for (int verticeHijo : g.ady(verticePadre)) {
				if (!marcados[verticeHijo]) {
					marcados[verticeHijo] = true;
					distTo[verticeHijo] = distTo[verticePadre] + 1;

					if (distTo[verticeHijo] % 2 == 0) {
						num_amigos++;
					}
					else {
						num_enemigos++;
					}
					q.push(verticeHijo);
				}
			}
		}

		numero_maximo += max(num_amigos, num_enemigos);
	};

public:
	prepara_fiesta(const Grafo& g): marcados(g.V(), false), distTo(g.V(), 0), numero_maximo(0){

		for (size_t i = 0; i < g.V(); i++){
			if (!marcados[i]) {
				bfs(g, i);
			}
		}

	};

	~prepara_fiesta() {};

	inline int solucion() const { return numero_maximo; };

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, P;
	cin >> N >> P;

    if (!std::cin)
        return false;

	Grafo g(N);

	for (size_t i = 0; i < P; i++){
		int a, b;
		cin >> a >> b;

		g.ponArista(a - 1, b - 1);
	}
    
	prepara_fiesta sol(g);
    // escribir sol
	cout << sol.solucion() << endl;
    
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