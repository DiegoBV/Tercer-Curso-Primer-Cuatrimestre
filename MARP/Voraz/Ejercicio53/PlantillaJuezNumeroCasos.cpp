// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void resuelveCaso() {
	int NumeroPilas, V;
	cin >> NumeroPilas >> V;
	vector<int> pilas;

	for (size_t i = 0; i < NumeroPilas; i++){
		int voltaje;
		cin >> voltaje;
		pilas.push_back(voltaje);
	}

	sort(pilas.begin(), pilas.end());
	int numCoches = 0;
	int i = 0; int j = pilas.size() - 1;

	while (j > i) { //si no se cruzan
		if (pilas[i] + pilas[j] >= V) {
			numCoches++;
			j--;
		}

		i++;
	}
	cout << numCoches << endl;
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

	for (int i = 0; i < numCasos; ++i) {
		resuelveCaso();
	}

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}