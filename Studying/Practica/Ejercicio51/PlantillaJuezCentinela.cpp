// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


int resuelve(const vector<int>& alturas, const vector<int>& longitudes) {
	int suma = 0;

	for (size_t i = 0; i < alturas.size(); i++){
		suma += abs(alturas[i] - longitudes[i]);
	}

	return suma;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	vector<int> alturas;
	for (size_t i = 0; i < N; i++){
		int h;
		cin >> h;

		alturas.push_back(h);
	}
	sort(alturas.begin(), alturas.end()); //n * log(n)

	vector<int> longitudes;
	for (size_t i = 0; i < N; i++){
		int l; 
		cin >> l;

		longitudes.push_back(l);
	}
	sort(longitudes.begin(), longitudes.end());
    
    // escribir sol
	cout << resuelve(alturas, longitudes) << endl;

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
