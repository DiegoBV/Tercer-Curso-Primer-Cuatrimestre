// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edificio
{
	int W, E;
	Edificio(int w, int e) : W(w), E(e) {};
};

bool operator <(const Edificio& e1, const Edificio& e2) { return e1.E > e2.E; };

int resuelve_Caso(priority_queue<Edificio>& edificios) {
	int numeroPuentes = 1;

	Edificio edificioActual = edificios.top();
	edificios.pop();

	while (!edificios.empty()){
		Edificio e = edificios.top();
		edificios.pop();
		if (edificioActual.E <= e.W ) { //edificios que no se cruzan (?) 
			numeroPuentes++;
			edificioActual = e;
		}
	}

	return numeroPuentes;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
    
	priority_queue<Edificio> edificios;
	for (size_t i = 0; i < N; i++){
		int W, E;
		cin >> W >> E;

		edificios.push(Edificio(W, E));
	}
	cout << resuelve_Caso(edificios) << endl;
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
