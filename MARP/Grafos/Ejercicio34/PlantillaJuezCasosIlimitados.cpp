// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "ConjuntosDisjuntos.h"

using namespace std;

vector<pair<int, int>> dirs;

int F, C;

//coste O(F*C), representa las manchas de petroleo por consola
void representa(const vector<string>& matriz) {
	cout << endl;
	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size(); j++) {
			cout << matriz[i][j];
		}
		cout << endl;
	}
}

//coste O(1), devuelve true si las coordenadas del vector son correctas --> estan dentro del rango del mismo
bool es_correcta(int ni, int nj, const vector<string>& matriz) {
	return (ni >= 0 && ni < matriz.size() && nj >= 0 && nj < matriz[ni].size());
}

//coste O(8), comprueba la adyacencia en las 8 direcciones del vector de strings
void adyacencia(ConjuntosDisjuntos& g, const vector<string>& matriz, int i, int j) {
	for (pair<int, int> nDir : dirs) {
		int nI = i + nDir.first;
		int nJ = j + nDir.second;
		if (es_correcta(nI, nJ, matriz) && matriz[nI][nJ] == '#') { //si su adyacente es mancha de petroleo, se establece union
			g.unir(i*C + j, nI*C + nJ); //se unen las posiciones
		}
	}
}

//coste O(F*C) ---> no ha sido necesario usarlo
unsigned int getMaxTam(const vector<string>& matriz, const ConjuntosDisjuntos& g) {
	unsigned int tam = 0;
	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size(); j++) {
			if (matriz[i][j] == '#') {
				unsigned int temp = g.tam(i*C + j);
				tam = max(temp, tam);
			}
		}
	}
	return tam;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	cin >> F >> C;
    if (! std::cin)
        return false;

	ConjuntosDisjuntos g(F*C); //creacion del conjunto disjunto
	vector<string> matriz; //matriz de chars, donde se comprueba la dyacencia
	matriz.resize(F);

	unsigned int maxTam = 0;

	//O(F*C)
	for (int i = 0; i < F; i++) {
		matriz[i].resize(C);
		for (int j = 0; j < C; j++) {
			char c;
			cin >> c;
			matriz[i][j] = c;
			if (c == '#') {
				adyacencia(g, matriz, i, j);
				maxTam = max(maxTam, (unsigned)g.tam(i*C + j));
			}
		}
	}

	cout << maxTam << " ";

	int N;
	cin >> N;

	//O(N)
	for (int i = 0; i < N; i++) {
		int nF, nC;
		cin >> nF >> nC;
		matriz[nF - 1][nC - 1] = '#';
		//ADYACENCIA
		adyacencia(g, matriz, nF - 1, nC - 1);
		maxTam = max(maxTam, (unsigned)g.tam((nF - 1)* C + (nC - 1)));
		cout << maxTam << " ";
	}

	cout << endl;

    return true;
    
}

int main() {
	dirs.resize(8);
	pair<int, int> p0(0, 1);
	pair<int, int> p1(0, -1);
	pair<int, int> p2(1, 0);
	pair<int, int> p3(-1, 0);
	pair<int, int> p4(1, 1);
	pair<int, int> p5(1, -1);
	pair<int, int> p6(-1, 1);
	pair<int, int> p7(-1, -1);
	dirs[0] = p0;
	dirs[1] = p1;
	dirs[2] = p2;
	dirs[3] = p3;
	dirs[4] = p4;
	dirs[5] = p5;
	dirs[6] = p6;
	dirs[7] = p7;
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