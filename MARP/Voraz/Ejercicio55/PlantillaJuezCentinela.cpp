// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int MINUTOS_LIBRES = 10;

struct Pelicula {
	int horaComienzo, horaFin, duracion, index;

	Pelicula(int hc, int hf, int duracion, int index) : horaComienzo(hc), horaFin(hf), duracion(duracion), index(index) {};
};

//esta el problema de que, por ejemplo, la primera duire un huevo
int resuelve(vector<Pelicula>& peliculas, vector<Pelicula>& auxHoras) {
	int numPelis = 1;
	for (size_t i = 0; i < peliculas.size(); i++){
		if (peliculas[i].index + 1 < auxHoras.size() && peliculas[i].horaFin + MINUTOS_LIBRES <= auxHoras[peliculas[i].index + 1].horaComienzo) { //si no solapa...
			numPelis++;
		}
	}

	return numPelis;
};

bool operator <(const Pelicula& p1, const Pelicula& p2) { return p1.duracion < p2.duracion; };
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
   
	vector<Pelicula> peliculas;
	vector<Pelicula> auxHoras;
	for (size_t i = 0; i < N; i++){
		string hc;
		cin >> hc;
		int hora = (hc[0] * 10 + hc[1]) * 60;
		int minutos = hc[3] + hc[4];

		int horaComienzo, duracion;
		cin >> duracion;
		horaComienzo = hora + minutos;
		peliculas.push_back(Pelicula(horaComienzo, horaComienzo + duracion, duracion, i));
		auxHoras.push_back(Pelicula(horaComienzo, horaComienzo + duracion, duracion, i));
	}
	sort(peliculas.begin(), peliculas.end());
	cout << resuelve(peliculas, auxHoras) << endl;

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
