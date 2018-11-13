// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

class resuelve {
private:
	bool islas_unidas;
	int coste_total;
public:
	resuelve() {};
	~resuelve() {};

	//kruskal tiene un coste de O(E*logE) siendo E el numero de puentes que hay
	resuelve(const int numeroVertices, PriorityQueue<Arista<int>>& heap): islas_unidas(false), coste_total(0) {

		ConjuntosDisjuntos u(numeroVertices);

		while (!heap.empty()){
			int v, w;
			v = heap.top().uno();
			w = heap.top().otro(v);
			if (!u.unidos(v, w)) {
				u.unir(v, w);
				coste_total += heap.top().valor();
			}
			heap.pop();
		}
		
		if (u.num_cjtos() == 1) {
			islas_unidas = true;
		}
	};

	int coste() const { return coste_total; };
	bool estan_unidas() const { return islas_unidas; };
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int I, P;
	cin >> I >> P;

    if (! std::cin)
        return false;

	PriorityQueue<Arista<int>> heap;

	for (size_t i = 0; i < P; i++){
		int isla1, isla2, coste;
		cin >> isla1 >> isla2 >> coste;
		Arista<int> a(isla1 - 1, isla2 - 1, coste);
		heap.push(a);
	}
    
	resuelve sol(I, heap);
    // escribir sol
	sol.estan_unidas() ? cout << sol.coste() : cout << "No hay puentes suficientes";
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