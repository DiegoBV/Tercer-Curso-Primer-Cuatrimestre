// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int resuelve_caso(const vector<int>& agujeros, const int L) {
	int numero_parches = 1;
	int ori = agujeros[0];

	for (size_t i = 0; i < agujeros.size(); i++){
		if (agujeros[i] > ori + L) {
			numero_parches++;
			ori = agujeros[i];
		}
	}

	return numero_parches;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, L;
	cin >> N >> L;

    if (! std::cin)
        return false;

	vector<int> agujeros;

	for (size_t i = 0; i < N; i++){
		int pos;
		cin >> pos;

		agujeros.push_back(pos);
	}
   
    
    // escribir sol
	cout << resuelve_caso(agujeros, L) << endl;
    
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