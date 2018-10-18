// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

/*class camino_mas_corto {
private:
	vector<bool> marcados;
	vector <int> distToOrigin;

	void bfs(const GrafoDirigido& g, int V) {
		queue<int> q;
		q.push(V);
		distToOrigin[V] = 0;
		marcados[V] = true;

		while (!q.empty()) {
			int fath = q.front();
			q.pop();

			for (int child : g.ady(fath)) {
				if (!marcados[child]) {
					marcados[child] = true;
					q.push(child);
					distToOrigin[child] = distToOrigin[fath] + 1;
				}
			}
		}
	};

public:

	camino_mas_corto() {};
	camino_mas_corto(const GrafoDirigido& g, int V) : marcados(g.V(), false), distToOrigin(g.V(), 0) {
		for (int i = 0; i < g.V(); i++) {
			if (!marcados[i]) {
				tiradas++;
				bfs(g, V);
			}
		}
	};

	void repr_dist_from_end_to_origin() {
		cout << distToOrigin[distToOrigin.size() - 1] << endl;
	};

	const int distancia_final_origen() {
		return distToOrigin[distToOrigin.size() - 1];
	};

};*/

int carasDado = 0;

struct casilla {
	int num;
	int saltoAl;

	casilla() : num(-1), saltoAl(-1) {}
	casilla(int numeroCasilla, int saltoA = -1) : num(numeroCasilla), saltoAl(saltoA) {};
};


class numero_tiradas {
private:
	vector<int> niveles;
	vector<bool> marcados;

	void bfs(const vector<casilla>& tablero, int vertice) {
		queue<casilla> q;
		q.push(tablero[vertice]);
		marcados[vertice] = true;

		while (!q.empty()) {
			casilla cas_a_explorar = q.front();
			q.pop();

			//adyacencia
			for (int i = cas_a_explorar.num; i <= (cas_a_explorar.num + carasDado) && i < tablero.size(); i++) {
				if (!marcados[i]) {

					marcados[i] = true;
					q.push(tablero[i]);
					niveles[i] = niveles[cas_a_explorar.num] + 1;

					if (tablero[i].saltoAl != -1 && !marcados[tablero[i].saltoAl]) {
						marcados[tablero[i].saltoAl] = true;
						q.push(tablero[tablero[i].saltoAl]);
						niveles[tablero[i].saltoAl] = niveles[cas_a_explorar.num] + 1;
					}
				}
			}
		}
	};

public:
	numero_tiradas() {};
	numero_tiradas(const vector<casilla>& tablero, int vertice): marcados(tablero.size(), false), niveles(tablero.size(), 0) {
		bfs(tablero, vertice);
	};

	const int getTiradas() {
		return niveles[niveles.size() - 1];
	}
};




// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K, S, E;
	cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && E == 0 && S == 0)
		return false;

	vector<casilla> tablero;
	tablero.resize(N*N);
	carasDado = K;

	for (int i = 0; i < tablero.size(); i++) {
		tablero[i].num = i;
	}

	for (int i = 0; i < (S + E); i++) {
		int elem1, elem2;
		cin >> elem1 >> elem2;
		tablero[elem1 - 1].num = elem1 - 1;
		tablero[elem1 - 1].saltoAl = elem2 - 1;
	}

	//camino_mas_corto sol(g, 0);

	// escribir sol
	//sol.repr_dist_from_end_to_origin();
	//cout << ceil((float)sol.distancia_final_origen() / (float)K) << endl;
	numero_tiradas sol(tablero, 0);
	cout << sol.getTiradas() << endl;

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