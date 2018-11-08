// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <climits>
#include <algorithm>
#include "ConjuntosDisjuntos.h"

using namespace std;

int fin = 0;
int fin_cercano = 0;
int in_cercano = 0;
int pto_medio_principio = INT_MAX;
int pto_medio_final = INT_MIN;
bool primera_vuelta = true;
int N, M;
pair<int, int> sol;

bool principio_final_unidos(ConjuntosDisjuntos& g) {
	return g.unidos(0, fin);
}

void comprueba_adyacencia(const pair<int, int>& v, const int& k, ConjuntosDisjuntos& g, vector<vector<int>>& bosque) {
	/*bool no_conecta = true;

	int compr = (v + k) - fin_cercano;

	if (compr >= 0) //significa que esta conectado con el final
	{
		no_conecta = false;
		g.unir(v, fin_cercano);
		if(v < fin_cercano)
			fin_cercano = v;
		if (pto_medio_final != INT_MIN && pto_medio_final + k - v >= 0) {
			g.unir(pto_medio_final, v);
			if (pto_medio_principio != INT_MAX) {
				fin_cercano = pto_medio_principio;
			}
		}
	}

	if ((in_cercano + k) - (v) >= 0){ //significa que esta conectado con el principio
		no_conecta = false;
		g.unir(in_cercano, v);
		if(v > in_cercano)
			in_cercano = v;
		if (pto_medio_principio != INT_MAX && v + k - pto_medio_principio >= 0) {
			g.unir(pto_medio_principio, v);
			if (pto_medio_final != INT_MIN) {
				in_cercano = pto_medio_final;
			}
		}
	}

	if (no_conecta) {
		if (pto_medio_final != INT_MIN) {
				g.unir(pto_medio_final, v);
		}
		else if(pto_medio_principio != INT_MAX){
			g.unir(pto_medio_principio, v);
		}

		if (v > pto_medio_final) {
			pto_medio_final = v;
		}
		else {
			pto_medio_principio = v;
		}
	}*/
	for (int i = k; i > -(k + 1); i--) {
		for (int j = -(k); j < (k + 1); j++) {
			int ni = v.first + i;
			int nj = v.second + j;
			if (ni >= 0 && ni < bosque.size() && nj >= 0 && nj < bosque[0].size()) {
				if (bosque[ni][nj] == 1) { //hay arbol
					pair<int, int> d = { v.first - ni, v.second - nj };
					float dist = sqrt((pow(d.first, 2) + (pow(d.second, 2))));
					if (dist <= k) {
						int e1 = v.first * (M + 1) + v.second;
						int e2 = ni * (M + 1) + nj;
						g.unir(e1, e2);
						if (principio_final_unidos(g)) {
							sol = v;
						}
					}
				}
			}
		}
	}


}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int K, n;
	cin >> N >> M >> K >> n;
	fin = (N * (M + 1) + M);
	/*in_cercano = 0;
	fin_cercano = fin;
	pto_medio_principio = INT_MAX;
	pto_medio_final = INT_MIN;*/

    if (! std::cin)
        return false;
   
	ConjuntosDisjuntos g((N+1)*(M+1));
	std::vector<vector<int>> bosque(N+1, vector<int>(M+1));
	stack<pair<int, int>> orden_inverso;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		//int v = x * (M + 1) + y;
		orden_inverso.push({x, y});
		//bosque[x][y] = 1;
	}
	bosque[0][0] = 1;
	bosque[N][M] = 1;

	pair<int, int> ve = {-1, -1};
	bool ppio_fin_estanUnidos = false;

	while (!orden_inverso.empty() && !ppio_fin_estanUnidos) { //La primera vez que se unen en el recorrido inverso, singifica que hemos encontrado el ultimo arbol que unia el principio con el final
		ve = orden_inverso.top();
		orden_inverso.pop();
		bosque[ve.first][ve.second] = 1;
		comprueba_adyacencia(ve, K, g, bosque); //va uniendo los vertices...
		ppio_fin_estanUnidos = principio_final_unidos(g);
	}
    
    // escribir sol
	
	//sol.first = ve / (M + 1);
	//sol.second = ve % (M + 1);

	ppio_fin_estanUnidos ? cout << sol.first << " " << sol.second : cout << "NUNCA SE PUDO";
	cout << endl;

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