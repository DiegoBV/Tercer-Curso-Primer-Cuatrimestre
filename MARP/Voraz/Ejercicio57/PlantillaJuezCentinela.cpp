// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
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
	return t1.c < t2.c;
};

bool estaEnRango(const Trabajo& t, const int c) {
	return t.c <= c;
};

bool estaMasCercaDelFin(const Trabajo& t, const Trabajo& temp, const int F) {
	return (abs(t.f - F) < abs(temp.f - F));
}

pair<int, bool> resuelve(vector<Trabajo>& proyectos, const int C, const int F) {
	int numProyectos = 0;
	int temp = C;
	bool es_posible = false;

	int i = 0;

	Trabajo t_temp;

	while (i < proyectos.size() && !es_posible){
		Trabajo t = proyectos[i];

		if (estaEnRango(t, temp)){
			if (estaMasCercaDelFin(t, t_temp, F)) {
				t_temp = t;
			}

			i++;
		}
		else {
			numProyectos++;
			if (numProyectos > proyectos.size()) break; //yolo
			temp = t_temp.f;
		}

		if (t_temp.f >= F) {
			es_posible = true;
		}

	}

	return { numProyectos, es_posible };
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
	pair<int, bool> sol = resuelve(proyectos, C, F);
	sol.second ? cout << sol.first + 1 : cout << "Imposible";
	cout << endl;
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
