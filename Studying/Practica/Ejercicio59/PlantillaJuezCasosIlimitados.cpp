// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int resuelve(const vector<int>& enemigos, const vector<int>& aliados) {
	int numeroVictorias = 0;

	int i = 0, j = 0;
	while (i < enemigos.size() && j < aliados.size()) {
		int allies = aliados[j];
		int enemies = enemigos[i];

		if (allies >= enemies) {
			numeroVictorias++;
			i++;
			j++;
		}
		else {
			j++;
		}
	}

	return numeroVictorias;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (!std::cin)
        return false;

	vector<int> enemigos;
	for (size_t i = 0; i < N; i++){
		int cant;
		cin >> cant;

		enemigos.push_back(cant);
	}

	sort(enemigos.begin(), enemigos.end());

	vector<int> aliados;
	for (size_t i = 0; i < N; i++){
		int cant;
		cin >> cant;

		aliados.push_back(cant);
	}

	sort(aliados.begin(), aliados.end());

	cout << resuelve(enemigos, aliados) << endl;;
    
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