// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int resuelve(const vector<int>& pilas, const int V) {
	int i = 0, j = pilas.size() - 1, numCoches = 0;

	while (i < j) {
		if (pilas[i] + pilas[j] >= V) {
			numCoches++;
			j--;
			i++;
		}
		else {
			i++;
		}
	}

	return numCoches;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int N, V;
	cin >> N >> V;
    
	vector<int> pilas;
	for (size_t i = 0; i < N; i++){
		int v;
		cin >> v;

		pilas.push_back(v);
	}

	sort(pilas.begin(), pilas.end());

    // escribir sol
	cout << resuelve(pilas, V) << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
	 int numCasos;
	 std::cin >> numCasos;
	 for (int i = 0; i < numCasos; ++i)
		 resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}