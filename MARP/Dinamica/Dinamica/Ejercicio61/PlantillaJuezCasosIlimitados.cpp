// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

struct Tesoro
{
	int p, cantidad_oro;

	Tesoro() {};
	Tesoro(int p, int c) : p(p), cantidad_oro(c) {};

};

void resuelve(vector<Tesoro>& tesoros, const int T, int& max_gold, vector<bool>& cuales, int& cuantos) {
	int n = tesoros.size() - 1;
	Matriz<int> botin(n + 1, T + 1, 0);

	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		for (int j = 1; j <= T; j++) {

			if (3 * tesoros[i].p > j) {
				botin[i][j] = botin[i - 1][j];
			}
			else {
				botin[i][j] = max(botin[i - 1][j], botin[i - 1][j - 3 * tesoros[i].p] + tesoros[i].cantidad_oro);
			}
		}
	}

	max_gold = botin[n][T];

	//calculo de los tesoros
	int resto = T;
	for (size_t i = n; i >= 1; i--)
	{
		if (botin[i][resto] == botin[i - 1][resto]) {
			//no cogemos objeto i
			cuales[i] = false;
		}
		else {
			//cogemos objeto i
			cuales[i] = true;
			cuantos++;
			resto = resto - 3 * tesoros[i].p;
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int T, N;
	cin >> T >> N;

    if (! std::cin)
        return false;
    
	vector<Tesoro> tesoros(N + 1);
	for (size_t i = 1; i <= N; i++)
	{
		int p, gold;
		cin >> p >> gold;

		tesoros[i] = {p, gold};
	}

	int max_gold = 0, cuantos = 0;
	vector<bool> cuales(T + 1, false);
	resuelve(tesoros, T, max_gold, cuales, cuantos);

    // escribir sol
	cout << max_gold << endl << cuantos << endl;
	for (size_t i = 0; i < cuales.size(); i++)
	{
		if (cuales[i]) {
			cout << tesoros[i].p << " " << tesoros[i].cantidad_oro << endl;
		}
	}
    
	cout << "----" << endl;

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