// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void pintaMatriz(Matriz<int>& matriz) {
	for (size_t i = 0; i < matriz.numfils(); i++) {
		for (size_t j = 0; j < matriz.numcols(); j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
};

void comida(vector<int>& cubos, int& cantMax) {
	Matriz<int> matriz(cubos.size(), cubos.size(), 0);

	//casos base
	for (int i = 0; i < matriz.numfils(); i++)
	{
		matriz[i][i] = cubos[i]; //primera diagonal
	}

	for (int i = 0; i < matriz.numfils() - 1; i++)
	{
		matriz[i][i + 1] = max(cubos[i], cubos[i + 1]);  //segunda diagonal
	}

	/*for (int d = 2; d < matriz.numfils(); d++) {
		for (int i = 0; i < matriz.numfils() - d; i++) {
			int j = i + d;

			int izq = (cubos[i + 1] > cubos[j]) ? matriz[i + 2][j] : matriz[i + 1][j - 1];
			int der = (cubos[i] > cubos[j - 1]) ? matriz[i + 1][j - 1] : matriz[i][j - 2];

			matriz[i][j] = max(izq + cubos[i], der + cubos[j]);
		}
	}*/
	//pintaMatriz(matriz);
	for (int i = matriz.numfils() - 3; i >= 0; i--)
	{
		for (int j = i + 2; j < matriz.numcols(); j++)
		{
			int izq = (cubos[i + 1] > cubos[j]) ? matriz[i + 2][j] : matriz[i + 1][j - 1];
			int der = (cubos[i] > cubos[j - 1]) ? matriz[i + 1][j - 1] : matriz[i][j - 2];
		
			matriz[i][j] = max(izq + cubos[i], der + cubos[j]);
		}
	}

	cantMax = matriz[0].back();
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;

	vector<int> cubos;
	for (size_t i = 0; i < N; i++){
		int cantidad;
		cin >> cantidad;

		cubos.push_back(cantidad);
	}
    
	int cantidad_maxima = 0;

	comida(cubos, cantidad_maxima);
    // escribir sol
	cout << cantidad_maxima << endl;
    
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
