// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"

using namespace std;

class recorre_ciudad
{
private:
	vector<bool> marcados;
	void dfs(const GrafoValorado<int>& g, const int& s, const int& anchura) {
		marcados[s] = true;
		for (Arista<int> e : g.ady(s)) {
			int w = e.otro(s);
			if (!marcados[w] && e.valor() >= anchura) {
				dfs(g, w, anchura);
			}
		}
	};

public:
	recorre_ciudad(const GrafoValorado<int>& g, const int& i1, const int& i2, const int& anchura): 
		marcados(g.V(), false) {
		dfs(g, i1, anchura);
	};

	~recorre_ciudad() {};

	inline const bool getSol(const int& dest) { return marcados[dest]; };
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int V, E;
	cin >> V >> E;
    if (!std::cin)
        return false;
	GrafoValorado<int> g(V);
	for (size_t i = 0; i < E; i++){
		int i1, i2, anchura;
		cin >> i1 >> i2 >> anchura;

		g.ponArista({ i1 - 1, i2 - 1, anchura });
	}
	int K;
	cin >> K;
	for (size_t i = 0; i < K; i++){
		int i1, i2, anchura;
		cin >> i1 >> i2 >> anchura;
		recorre_ciudad sol(g, i1 - 1, i2 - 1, anchura);
		sol.getSol(i2 - 1) ? cout << "SI" << endl : cout << "NO" << endl;
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