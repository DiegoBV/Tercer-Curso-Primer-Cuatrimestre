// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

class resuelve
{
private:
	vector<bool> marcados;
	bool se_puede;
	int anchura_max;

	void dfs(const GrafoValorado<int>& mapa, int v) {
		marcados[v] = true;
		for (Arista<int> w : mapa.ady(v)) {
			int child = w.otro(v);
			if (!marcados[child] && anchura_max <= w.valor()) {
				dfs(mapa, child);
			}
		}
	};

public:

	resuelve(const GrafoValorado<int>& mapa, const int origen, const int dest, const int a) :
		marcados(mapa.V(), false), se_puede(false), anchura_max(a) {
		dfs(mapa, origen);
		se_puede = marcados[dest];
	};

	~resuelve() {};

	inline const bool getSol() { return se_puede; };

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int V, E;
	cin >> V >> E;
    if (! std::cin)
        return false;
    
	GrafoValorado<int> mapa(V);
	for (size_t i = 0; i < E; i++){
		int in1, in2, anchura;
		cin >> in1 >> in2 >> anchura;

		mapa.ponArista({ in1 - 1, in2 - 1, anchura });
	}

	int K;
	cin >> K;
	
	for (size_t i = 0; i < K; i++){
		int c_in1, c_in2, c_anchura;
		cin >> c_in1 >> c_in2 >> c_anchura;

		resuelve sol(mapa, c_in1 - 1, c_in2 - 1, c_anchura);
		sol.getSol() ? cout << "SI" << endl : cout << "NO" << endl;
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