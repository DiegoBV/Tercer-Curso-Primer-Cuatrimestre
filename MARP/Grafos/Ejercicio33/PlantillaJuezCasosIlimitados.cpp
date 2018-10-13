// Nombre del alumno DIEGO BARATTO VALDIVIA
// Usuario del Juez VJ15

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Grafo.h"

using namespace std;

vector<pair<int, int>> dirs;


class cuentaConexas {
private:
	vector<bool> marcados;
	int numConexas_;

	void deep_search(const Grafo& g, const int v) {
		marcados[v] = true;
		for (int i : g.ady(v)) {
			if (!marcados[i]) {
				deep_search(g, i);
			}
		}
	};

public:
	cuentaConexas() {};
	cuentaConexas(const Grafo& g, const vector<bool>& b): marcados(g.V(), false), numConexas_(0) {
		for (int i = 0; i < g.V(); i++) {
			if (!marcados[i] && b[i]) { //si encuentra algun vertice sin marcar, es otra componente conexa
				numConexas_++;
				deep_search(g, i);
			}
		}

	};

	int getNumConexas() const { return numConexas_; };
};

void comprueba_adyacencia(const vector<vector<char>>& v, const vector<vector<int>>& v_aux, const char& c, Grafo& g, int pi, int pj, const vector<bool>& b) {
	for (int i = 0; i < dirs.size(); i++) {
		int ni, nj;
		ni = pi + dirs[i].first;
		nj = pj + dirs[i].second;

		if (ni >= 0 && ni < v.size() && nj >= 0 && nj < v[i].size() && !b[ni*v[ni].size() + nj]) { //la ultima condicion es para no poner aristas repetidas...
			if (v[ni][nj] == c) { //si es el mismo char, hay adyacencia
				g.ponArista(v_aux[ni][nj], v_aux[pi][pj]);
			}
		}
	}
}

// función que resuelve el problema
/*TipoSolucion resolver(TipoDatos datos) {
    
    
}*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int h = 0, w = 0;
	cin >> w >> h; //ancho y alto de la foto


	if (!std::cin)
		return false;

	Grafo g(w*h);
	vector<vector<char>> v; //vector para la matriz de la foto
	vector<vector<int>> v_aux; //vector de vertices del grafo
	vector<bool> b; //vector de bool, indica si un vertice es blanco o no
	b.resize(w*h);

	int index = 0;

	//lectura del archivo de datos
	for (int i = 0; i < h; i++) {
		v.push_back(vector<char>());
		v_aux.push_back(vector<int>());
		for (int j = 0; j < w; j++) {
			char nElem;
			cin >> nElem;
			v[i].push_back(nElem);
			v_aux[i].push_back(index); //numero del vertice
			index++;
		}
	}

	//coste O(v) siendo v el numero de vertices
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {	
			int p = i * w + j;

			comprueba_adyacencia(v, v_aux, v[i][j], g, i, j, b); //comprueba la adyacencia, es decir, añade las aristas correspondientes --> problema, pone aristas innecesarias ? igual da tl

			if (v[i][j] == '.') { //si el vertice es blanco, lo marca para su futura exploracion
				b[p] = true;
			}
		}
	}

	//g.print(cout);


    // escribir sol

	cuentaConexas c(g, b);

	cout << c.getNumConexas() - 1 << endl;
    
    return true;
}

int main() {
	dirs.resize(4);
	pair<int, int> p0(0, 1);
	pair<int, int> p1(0, -1);
	pair<int, int> p2(1, 0);
	pair<int, int> p3(-1, 0);
	dirs[0] = p0;
	dirs[1] = p1;
	dirs[2] = p2;
	dirs[3] = p3;

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