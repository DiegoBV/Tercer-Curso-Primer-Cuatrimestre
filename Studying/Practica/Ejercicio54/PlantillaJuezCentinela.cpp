// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct MyStruct
{
	bool operator()(const pair<int, int> p1, const pair<int, int> p2) { return p1.second > p2.second; };
};


int resuelve(const vector<pair<int, int>>& edificios) {
	int numPuentes = 1;

	pair<int, int> offset = edificios[0];

	for (size_t i = 1; i < edificios.size(); i++){
		if (offset.second >= edificios[i].second) {
			numPuentes++;
			offset = edificios[i];
		}
	}

	return numPuentes;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	vector<pair<int, int>> edificios;
	for (size_t i = 0; i < N; i++){
		int w, e;
		cin >> w >> e;

		edificios.push_back({ w, e });
	}

	sort(edificios.begin(), edificios.end(), MyStruct());
    // escribir sol
	cout << resuelve(edificios) << endl;

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
