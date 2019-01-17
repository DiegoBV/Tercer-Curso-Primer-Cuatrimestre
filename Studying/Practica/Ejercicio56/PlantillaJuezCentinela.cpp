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
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) { return p1.first < p2.first; };
};

void liberaPersonas(vector<int>& tiempos_fin, const int start, int& numPers) {
	for (vector<int>::iterator it = tiempos_fin.begin(); it != tiempos_fin.end();) {
		if (start >= *it) {
			numPers--;
			it = tiempos_fin.erase(it);
		}
		else {
			++it;
		}
	}
};

int resuelve(const vector<pair<int, int>>& actividades) {
	int numPersonas = 0;
	pair<int, int> offset = actividades[0];
	vector<int> tiempos_fin;

	for (size_t i = 1; i < actividades.size(); i++){
		if (offset.second > actividades[i].first) {
			numPersonas++;
			tiempos_fin.push_back(actividades[i].second);
		}
		else {
			offset = actividades[i];
			tiempos_fin.push_back(offset.second);
		}
		liberaPersonas(tiempos_fin, actividades[i].first, numPersonas);
	}

	return numPersonas;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	vector<pair<int, int>> actividades;
	for (size_t i = 0; i < N; i++){
		int tc, tf;
		cin >> tc >> tf;

		actividades.push_back({ tc, tf });
	}

	sort(actividades.begin(), actividades.end(), MyStruct());
    // escribir sol
	cout << resuelve(actividades) << endl;
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
