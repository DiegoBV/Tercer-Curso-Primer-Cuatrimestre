// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "ConjuntosDisjuntos.h"

using namespace std;
int F, C;
vector<pair<int, int>> dirs;

bool es_correcta(int ni, int nj, const vector<string>& matriz) {
	return (ni >= 0 && ni < F && nj >= 0 && nj < C);
}

void adyacencia(ConjuntosDisjuntos& cjto, const vector<string>& foto, const int i, const int j) {
	for (pair<int, int> dir : dirs) {
		int ni = i + dir.first;
		int nj = j + dir.second;
		if (es_correcta(ni, nj, foto) && foto[ni][nj] == '#'){
			cjto.unir(i*C + j, ni*C + nj);
		}
	}
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	
	cin >> F >> C;

    if (!std::cin)
        return false;
	ConjuntosDisjuntos cjto(F*C);
	vector<string> foto(F, string(C, 0));
	int max_ = 0;
	for (size_t i = 0; i < F; i++){
		for (size_t j = 0; j < C; j++) {
			char c;
			cin.get(c);
			if (c == '\n') {
				cin.get(c);
			}
			foto[i][j] = c;
			if (c == '#') {
				adyacencia(cjto, foto, i, j);
				max_ = max(max_, cjto.tam(i*C + j));
			}
		}
	}
	cout << max_ << " ";

	int N;
	cin >> N;
	for (size_t i = 0; i < N; i++){
		int f, c;
		cin >> f >> c;

		foto[f - 1][c - 1] = '#';
		adyacencia(cjto, foto, f - 1, c - 1);
		max_ = max(max_, cjto.tam((f - 1)*C + (c - 1)));

		cout << max_ << " ";
	}
    // escribir sol
    
    
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