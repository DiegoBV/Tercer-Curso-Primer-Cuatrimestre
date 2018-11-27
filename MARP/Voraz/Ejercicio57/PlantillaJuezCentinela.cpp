// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Trabajo
{
	int c, f;

	Trabajo() : c(-100), f(-100) {};
	Trabajo(int c, int f) : c(c), f(f) {};
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool operator <(const Trabajo& t1, const Trabajo& t2) {
	return t1.f > t2.f;
}

int resuelve(vector<Trabajo>& proyectos, const int C, const int F) {
	int numProyectos = 0;
	int temp = C;

	for (size_t i = 0; i < proyectos.size(); i++){

	}
}

bool resuelveCaso() {
    // leer los datos de la entrada
	int C, F, N;
	cin >> C >> F >> N;

    if (C == 0 && F == 0 && N == 0)
        return false;
   
	vector<Trabajo> proyectos;
	for (size_t i = 0; i < N; i++){
		int c, f;
		cin >> c >> f;

		proyectos.push_back({ c, f });
	}
	std::sort(proyectos.begin(), proyectos.end());
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
