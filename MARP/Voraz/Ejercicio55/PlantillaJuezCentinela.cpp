// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pelicula {
	int horaComienzo, horaFin;

	Pelicula(int hc, int hf) : horaComienzo(hc), horaFin(hf) {};
};

int resuelve(vector<Pelicula>& peliculas) {
	int numPelis = 1;
	Pelicula peliActual = peliculas[0];

	for (size_t i = 1; i < peliculas.size(); i++){
		if (peliActual.horaFin <= peliculas[i].horaComienzo) {
			peliActual = peliculas[i];
			numPelis++;
		}
	}

	return numPelis;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
   
	vector<Pelicula> peliculas;
	for (size_t i = 0; i < N; i++){
		string hc;
		cin >> hc;
		int hora = (hc[0] * 10 + hc[1]) * 60;
		int minutos = hc[3] + hc[4];

		int horaComienzo, duracion;
		cin >> duracion;
		horaComienzo = hora + minutos;
		peliculas.push_back(Pelicula(horaComienzo, horaComienzo + duracion));
	}	

	cout << resuelve(peliculas) << endl;

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
