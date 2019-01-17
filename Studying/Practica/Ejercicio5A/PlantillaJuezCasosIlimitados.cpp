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
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) { 
		return abs(p1.first - p1.second) < abs(p2.first - p2.second); };
};

int resuelve(const vector<pair<int, int>>& aviones, int L) {
	int numAviones = 0;

	for (size_t i = 0; i < aviones.size(); i++){
		if (abs(aviones[i].first - aviones[i].second) <= L) {
			numAviones++;
			L -= abs(aviones[i].first - aviones[i].second);
		}
	}

	return numAviones;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, L;
	cin >> N >> L;

    if (!std::cin)
        return false;
	vector<pair<int, int>> aviones;
	for (size_t i = 0; i < N; i++){
		int capacidad, litros_Actuales;
		cin >> capacidad >> litros_Actuales;

		aviones.push_back({ capacidad, litros_Actuales });
	}
    
	sort(aviones.begin(), aviones.end(), MyStruct());

    // escribir sol
	cout << resuelve(aviones, L) << endl;

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