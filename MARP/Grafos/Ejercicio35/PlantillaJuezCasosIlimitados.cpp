// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include "ConjuntosDisjuntos.h"

using namespace std;

int fin = 0;
int fin_cercano = 0;
int in_cercano = 0;

void comprueba_adyacencia(const int& v, const int& k, ConjuntosDisjuntos& g) {
	int compr = (v + k) - fin_cercano;

	if (compr >= 0) //significa que esta conectado con el final
	{
		g.unir(v, fin_cercano);
		fin_cercano = v;
	}

	if ((in_cercano + k) - (v) >= 0){ //significa que esta conectado con el principio
		g.unir(in_cercano, v);
		in_cercano = v;
	}
}

bool principio_final_unidos(ConjuntosDisjuntos& g) {
	return g.unidos(0, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, M, K, n;
	cin >> N >> M >> K >> n;
	fin = (N * (M + 1) + M);
	in_cercano = 0;
	fin_cercano = fin;

    if (! std::cin)
        return false;
   
	ConjuntosDisjuntos g((N+1)*(M+1));
	stack<int> orden_inverso;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		int v = x * (M + 1) + y;
		orden_inverso.push(v);
	}

	int ve = -1;
	bool ppio_fin_estanUnidos = false;

	while (!orden_inverso.empty() && !ppio_fin_estanUnidos) { //La primera vez que se unen en el recorrido inverso, singifica que hemos encontrado el ultimo arbol que unia el principio con el final
		ve = orden_inverso.top();
		orden_inverso.pop();
		comprueba_adyacencia(ve, K*(M + 1), g); //va uniendo los vertices...
		ppio_fin_estanUnidos = principio_final_unidos(g);
	}
    
    // escribir sol
	pair<int, int> sol;
	sol.first = ve / (M + 1);
	sol.second = ve % (M + 1);

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