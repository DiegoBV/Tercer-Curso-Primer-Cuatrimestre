// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int resuelve(const vector<int>& posiciones, const int L) {
	if (posiciones.empty()) {
		return 0;
	}

	int offset = posiciones[0]; //primer agujero
	int numeroParches = 1;

	for (size_t i = 1; i < posiciones.size(); i++){
		if (offset + L < posiciones[i]) {
			offset = posiciones[i];
			numeroParches++;
		}
	}

	return numeroParches;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, L;
	cin >> N >> L;
    if (!std::cin)
        return false;
	vector<int> posiciones;
	for (size_t i = 0; i < N; i++){
		int pos;
		cin >> pos;

		posiciones.push_back(pos);
	}
    
    // escribir sol
	cout << resuelve(posiciones, L) << endl;

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