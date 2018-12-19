// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

void monedas(vector<int>& valores, vector<int>& cantidades, const int& precio, int& cantidad) {
	int n = valores.size() - 1;
	Matriz<int> matriz(n + 1, precio + 1, 1E9);

	matriz[0][0] = 0;           
	for (size_t i = 1; i <= n; i++){
		matriz[i][0] = 0;  //caso base
		for (size_t j = 1; j <= precio; j++){
			if (valores[i] > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				int k = 0;
				int minimo = matriz[i - 1][j];
				while (k <= cantidades[i] && k*valores[i] <= j){
					minimo = min(minimo, matriz[i - 1][j - k * valores[i]] + k);
					k++;
				}
				matriz[i][j] = minimo;
			}
		}
	}

	cantidad = matriz[n][precio];
};

void monedas2(vector<int>& valores, vector<int>& cantidades, const int& precio, int& cantidad) {
	vector<int> matriz(precio + 1, 1E9);
	matriz[0] = 0;
	int n = valores.size() - 1;
	for (size_t i = 1; i <= n; i++)
	{
		for (int j = precio; j > 0; j--) {

			int k = 0;
			int minimo = matriz[j];
			while (k <= cantidades[i] && k*valores[i] <= j) {
				minimo = min(minimo, matriz[j - k * valores[i]] + k);
				k++;
			}
			matriz[j] = minimo;

		}
	}

	cantidad = matriz[precio];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (!std::cin)
        return false;

	vector<int> valores(N + 1);
	for (size_t i = 1; i <= N; i++)
	{
		int valor;
		cin >> valor;

		valores[i] = valor;
	}
	
	vector<int> cantidades(N + 1);
	for (size_t i = 1; i <= N ; i++)
	{
		int cantidad;
		cin >> cantidad;

		cantidades[i] = cantidad;
	}

	int precio;
	cin >> precio;
    
	int cantidad;
	monedas2(valores, cantidades, precio, cantidad);
    // escribir sol
	(cantidad != 1E9) ? cout << "SI " << cantidad : cout << "NO";
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