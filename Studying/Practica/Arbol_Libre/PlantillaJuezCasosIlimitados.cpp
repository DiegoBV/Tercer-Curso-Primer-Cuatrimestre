// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "ConjuntosDisjuntos.h"

using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int V, A;
	cin >> V >> A;
    if (!std::cin)
        return false;

	bool es_libre = true;
	ConjuntosDisjuntos g(V);

	for (size_t i = 0; i < A; i++){
		int e1, e2;
		cin >> e1 >> e2;

		if (g.unidos(e1, e2)) {
			es_libre = false;
		}
		else {
			g.unir(e1, e2);
		}

	}

	if (g.num_cjtos() != 1) {
		es_libre = false;
	}

    // escribir sol
	es_libre ? cout << "SI" << endl : cout << "NO" << endl;
    
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