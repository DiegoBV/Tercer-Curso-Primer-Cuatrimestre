// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


int resuelve(priority_queue<int, vector<int>, greater<int>>& altura_esquiadores, priority_queue<int, vector<int>, greater<int>> longitud_esquis) {
	unsigned int suma_diferencias = 0;

	while (!altura_esquiadores.empty()) {
		int h = altura_esquiadores.top();
		altura_esquiadores.pop();

		int l = longitud_esquis.top();
		longitud_esquis.pop();

		suma_diferencias += (abs(h - l));
	}

	return suma_diferencias;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
	
	priority_queue<int, vector<int>, greater<int>> altura_esquiadores;
	for (size_t i = 0; i < N; i++){
		int h;
		cin >> h;

		altura_esquiadores.push(h);
	}

	priority_queue<int, vector<int>, greater<int>> longitud_esquis;
	for (size_t i = 0; i < N; i++) {
		int h;
		cin >> h;

		longitud_esquis.push(h);
	}
    
    // escribir sol
	cout << resuelve(altura_esquiadores, longitud_esquis) << endl;

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
