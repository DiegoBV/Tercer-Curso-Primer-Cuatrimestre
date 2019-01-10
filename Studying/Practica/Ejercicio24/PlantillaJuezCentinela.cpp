// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

void resuelve(const int N) {
	PriorityQueue<int> min;
	PriorityQueue<int, std::greater<int>> max;
	int currMediana = 0;

	for (size_t i = 0; i < N; i++){
		int elemento;
		cin >> elemento;

		if (elemento > currMediana/2) {
			min.push(elemento);
		}
		else {
			max.push(elemento);
		}

		if (max.size() > min.size() + 1) {
			min.push(max.top());
			max.pop();
		}
		else if (min.size() > max.size() + 1) {
			max.push(min.top());
			min.pop();
		}

		if ((max.size() + min.size()) % 2 == 0) {
			currMediana = (max.top() + min.top());
		}
		else if(max.size() > min.size()){
			currMediana = max.top() * 2;
		}
		else {
			currMediana = min.top() * 2;
		}

		cout << currMediana << " ";
	}

	cout << endl;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;
    
	resuelve(N);
    
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
