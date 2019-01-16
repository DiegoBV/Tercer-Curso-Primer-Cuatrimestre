// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int TIEMPO_PALOMITAS = 10;

struct MyStruct
{
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) { return p1.first < p2.first; };
};

int; i < peliculas.size(); i++){ resuelve(const vector<pair<int, int>>& peliculas) {
	int numPelis = 1;
	pair<int, int> offset = peliculas[0];

	for (size_t i = 1
		if (offset.second + TIEMPO_PALOMITAS <= peliculas[i].first) {
			//puedo verla
			numPelis++;
			offset = peliculas[i];
		}
		else {
			if (offset.second > peliculas[i].second) {
				offset = peliculas[i];
			}
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

	vector<pair<int, int>> peliculas;
	for (size_t i = 0; i < N; i++){
		string hora;
		int duracion;
		cin >> hora >> duracion;

		int h = (hora[0] - '0') * 10 + hora[1] - '0';
		int minutos = (hora[3] - '0') * 10 + hora[4] - '0';

		peliculas.push_back({ h * 60 + minutos, h * 60 + minutos + duracion });
	}

	sort(peliculas.begin(), peliculas.end());

    // escribir sol
	cout << resuelve(peliculas) << endl;

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
