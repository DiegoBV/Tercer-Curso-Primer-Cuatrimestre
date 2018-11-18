// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

int resuelve(priority_queue<int>& rivales, priority_queue<int, vector<int>, greater<int>>& broncos) {
	int suma_ = 0;

	while (!rivales.empty()) {
		int puntos_rivales = rivales.top();
		rivales.pop();

		int puntos_broncos = broncos.top();
		broncos.pop();

		if (puntos_broncos > puntos_rivales) { //los broncos ganan
			suma_ += (puntos_broncos - puntos_rivales);
		}
	}

	return suma_;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
    
	priority_queue<int> rivales;
	for (size_t i = 0; i < N; i++){
		int p;
		cin >> p;

		rivales.push(p);
	}

	priority_queue<int, vector<int>, greater<int>> broncos;
	for (size_t i = 0; i < N; i++){
		int p;
		cin >> p;

		broncos.push(p);
	}
    
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
