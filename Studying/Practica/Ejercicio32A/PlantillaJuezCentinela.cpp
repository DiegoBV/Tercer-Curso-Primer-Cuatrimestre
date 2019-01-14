// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "GrafoDirigido.h"

using namespace std;

int K;

class resuelve
{
private:
	vector<bool> marcados;
	vector<int> distTo;
	int numero_minimo;

	void bfs(const GrafoDirigido& tablero, const int V) {
		queue<int> q;
		distTo[V] = 0;
		marcados[V] = true;
		q.push(V);

		while (!q.empty()){
			int v = q.front();
			q.pop();

			for (int i = v + 1; i <= v + K; i++) {
				if (i < tablero.V()) {
					if (!marcados[i]) {
						for (int w : tablero.ady(i)) {
							if (!marcados[w]) {
								distTo[w] = distTo[v] + 1;
								marcados[w] = true;
								q.push(w);
							}
						}

						distTo[i] = distTo[v] + 1;
						q.push(i);
						marcados[i] = true;
					}
				}
			}
		}
	};

public:
	resuelve(const GrafoDirigido& tablero) : marcados(tablero.V(), false), distTo(tablero.V(), 0),
		numero_minimo(0) {

		bfs(tablero, 1);

		numero_minimo = distTo[tablero.V() - 1];

	};
	~resuelve() {};

	inline const int getSol() { return numero_minimo; };

};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, S, E;
	cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && S == 0 && E == 0)
		return false;
    
	GrafoDirigido tablero(N*N);
	for (size_t i = 0; i < (E + S); i++){
		int v, w;
		cin >> v >> w;

		tablero.ponArista(v - 1, w - 1);
	}
    
	resuelve sol(tablero);
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
