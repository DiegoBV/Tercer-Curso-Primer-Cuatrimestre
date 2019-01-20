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
	int gravedad, tiempo;
	string nombre;

	Paciente() {};
	Paciente(int g, int t, string n) : gravedad(g), tiempo(t), nombre(n) {};
};

struct comparador {
	bool operator()(const Paciente& p1, const Paciente& p2) {
		return (p1.gravedad > p2.gravedad ||
			(p1.gravedad == p2.gravedad && p1.tiempo < p2.tiempo));
	};
};

void ingresoPaciente(PriorityQueue<Paciente, comparador>& cola_espera, const int t) {
	string nombre;
	int gravedad;

	cin >> nombre >> gravedad;

	cola_espera.push({ gravedad, t, nombre });
};

void atenderPaciente(PriorityQueue<Paciente, comparador>& cola_espera) {
	cout << cola_espera.top().nombre << endl;
	cola_espera.pop();
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	PriorityQueue<Paciente, comparador> cola_espera;
	for (size_t i = 0; i < N; i++){
		char evento;
		cin >> evento;

		if (evento == 'I') {
			ingresoPaciente(cola_espera, i);
		}
		else if (evento == 'A') {
			atenderPaciente(cola_espera);
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
