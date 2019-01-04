// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

struct Paciente
{
	string name;
	int gravedad, tiempo;

	Paciente() {};
	Paciente(string n, int g, int t) : name(n), gravedad(g), tiempo(t) {};
};

bool operator <(const Paciente& p1, const Paciente& p2) {
	return ((p1.gravedad > p2.gravedad)
		|| ((p1.gravedad == p2.gravedad) && (p1.tiempo < p2.tiempo)));
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	PriorityQueue<Paciente> pQueue;
	for (int i = 0; i < N; i++){
		char c;
		cin >> c;
		if (c == 'I') {
			string name;
			int gravedad;
			cin >> name >> gravedad;
			pQueue.push({name, gravedad, i});
		}
		else if (c == 'A') {
			Paciente p = pQueue.top();
			pQueue.pop();

			cout << p.name << endl;
		}
	}
    
	cout << "----" << endl;
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
