// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int resuelve(const vector<int>& rivales, const vector<int>& broncos) {
	int suma = 0;

	for (size_t i = 0; i < broncos.size(); i++){
		if (broncos[i] > rivales[i]) {
			suma += (broncos[i] - rivales[i]);
		}
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

	vector<int> rivales;
	for (size_t i = 0; i < N; i++){
		int ptos;
		cin >> ptos;

		rivales.push_back(ptos);
	}
	sort(rivales.begin(), rivales.end());

	vector<int> broncos;
	for (size_t i = 0; i < N; i++){
		int ptos;
		cin >> ptos;

		broncos.push_back(ptos);
	}
	sort(broncos.rbegin(), broncos.rend());
    
    // escribir sol
	cout << resuelve(rivales, broncos) << endl;

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
