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
	vector<vector<bool>> marcados;
	int numConexas_;

	bool correcta(const int ni, const int nj) {
		return ni >= 0 && ni < marcados.size() && nj >= 0 && nj < marcados[0].size();
	};

	void deep_search(const vector<string>& g, const int i, const int j) {
		marcados[i][j] = true;

		for (pair<int, int> d : dirs) { 
			int ni, nj;
			ni = i + d.first;
			nj = j + d.second;

			if (correcta(ni, nj) && !marcados[ni][nj] && g[ni][nj] == '.') {
				deep_search(g, ni, nj); //O(v) siendo v el numero de adyacencias
			}
		}

	};

public:
	cuentaConexas() {};
	//coste O(i*j)
	cuentaConexas(const vector<string>& g): marcados(g.size(), vector<bool>(g[0].size(), false)), numConexas_(0) {
		for (int i = 0; i < g.size(); i++) {
			for (int j = 0; j < g[i].size(); j++) {
				if (g[i][j] == '.' && !marcados[i][j]) {
					numConexas_++;
					deep_search(g, i, j);
				}
			}
		}

	};

	int getNumConexas() const { return numConexas_; };
};

void comprueba_adyacencia(const vector<string>& v, const vector<vector<int>>& v_aux, const char& c, Grafo& g, int pi, int pj, const vector<bool>& b) {
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
};

void representa(const vector<string>& v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	
	cout << endl;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int h = 0, w = 0;
	cin >> w >> h; //ancho y alto de la foto


	if (!std::cin)
		return false;

	vector<string> v; //vector para la matriz de la foto

	int index = 0;

	//lectura del archivo de datos
	for (int i = 0; i < h; i++) {
		v.push_back(string());
		for (int j = 0; j < w; j++) {
			char nElem;
			cin >> nElem;
			v[i].push_back(nElem);
		}
	}

	//representa(v);

    // escribir sol

	cuentaConexas c(v);

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