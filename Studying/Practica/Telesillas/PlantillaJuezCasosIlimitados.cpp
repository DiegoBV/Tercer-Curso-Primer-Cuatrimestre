// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int resuelve(const vector<int>& pesos, const int& PESO_MAXIMO) {
	int numeroViajes = 0;
	int i = 0, j = pesos.size() - 1;

	while (i <= j) {
		int persona1 = pesos[i];
		int persona2 = pesos[j];

		if (persona1 + persona2 > PESO_MAXIMO) {
			j--;
		}
		else {
			i++;
			j--;
		}
		numeroViajes++;
	}
	return numeroViajes;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int P, N;
	cin >> P >> N;
    if (!std::cin)
        return false;
	vector<int> pesos;
	for (size_t i = 0; i < N; i++){
		int peso;
		cin >> peso;

		pesos.push_back(peso);
	}

	sort(pesos.begin(), pesos.end(), less<int>());
    
	cout << resuelve(pesos, P) << endl;
    // escribir sol
    
    
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