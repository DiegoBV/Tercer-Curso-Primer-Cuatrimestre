// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
#include <algorithm>

using namespace std;
vector<pair<int, int>> dir;

class calcula_mancha {
private:
	int tam_;
	vector<bool> marcados;
	void dps(const Grafo& g, const int V, int& nuevoTam) {
		marcados[V] = true;
		nuevoTam++;
		for (int i : g.ady(V)) {
			if (!marcados[i]) {
				dps(g, i, nuevoTam);
			}
		}
	}
public:
	calcula_mancha(const Grafo& g): tam_(0), marcados(g.V(), false) {
		for (int i = 0; i < g.V(); i++) {
			if (!marcados[i]) { //nueva mancha
				int nTam = 0;
				dps(g, i, nTam);
				tam_ = max(tam_, nTam);
			}
		}
	}

	int getTam() const { return tam_; };
};

void representa_manchas(const vector<vector<char>>& v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j];
		}
		cout << endl;
	}

	cout << endl << endl;
};

void adyacencia(Grafo& g, const vector<vector<char>>& v, const vector<vector<int>>& indices, const int V, const char c, const int pi, const int pj) {
	for (int i = 0; i < dir.size(); i++) {
		int nI, nJ;
		nI = pi - dir[i].first;
		nJ = pj - dir[i].second;

		if (nI >= 0 && nI < v.size() && nJ >= 0 && nJ < v[0].size()) {
			if (v[nI][nJ] == c) { //hay adyacencia
				g.ponArista(V, indices[nI][nJ]);
			}
		}
	}
};

void representa_sol(const Grafo& g) {
	calcula_mancha calc(g);
	// escribir sol
	cout << calc.getTam() << " ";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int F, C;
	cin >> F >> C; //filas y columnas

    if (! std::cin)
        return false;

	Grafo g(F*C);
	vector<vector<char>> v;
	vector<vector<int>> indices;

	int index = 0;
	//lectura del archivo de datos
	for (int i = 0; i < F; i++) {
		v.push_back(vector<char>());
		indices.push_back(vector<int>());
		for (int j = 0; j < C; j++) {
			char nElem;
			cin >> nElem;
			v[i].push_back(nElem);
			indices[i].push_back(index); //numero del vertice
			index++;
		}
	}

	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			int p = i * C + j;
			if (v[i][j] == '#') {
				adyacencia(g, v, indices, indices[i][j], v[i][j], i, j);
			}
		}
	}
	
	//representa_manchas(v);

	representa_sol(g);
	int N;
	cin >> N; //numero de nuevas fotos

	for (int i = 0; i < N; i++) {
		int nF, nC;
		cin >> nF >> nC; //mancha nueva
		v[nF-1][nC-1] = '#';
		adyacencia(g, v, indices, indices[nF - 1][nC - 1], v[nF - 1][nC - 1], nF - 1, nC - 1);
		representa_sol(g);
		//representa_manchas(v);
	}

	cout << endl;
    
    return true;
    
}

int main() {
	dir.resize(8);
	pair<int, int> p0(0, 1);
	pair<int, int> p1(0, -1);
	pair<int, int> p2(1, 0);
	pair<int, int> p3(-1, 0);
	pair<int, int> p4(1, 1);
	pair<int, int> p5(1, -1);
	pair<int, int> p6(-1, 1);
	pair<int, int> p7(-1, -1);
	dir[0] = p0;
	dir[1] = p1;
	dir[2] = p2;
	dir[3] = p3;
	dir[4] = p4;
	dir[5] = p5;
	dir[6] = p6;
	dir[7] = p7;
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