// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include"Matriz.h"

using namespace std;

struct Varilla
{
	int longitud, coste;

	Varilla() {};
	Varilla(int l, int c) : longitud(l), coste(c) {};
};

void varillas(vector<Varilla>& varillas, int L, int& numFormas) 
{
	Matriz<int> matriz(varillas.size(), L + 1, 0);

	int longitud_ = L;

	//rellenar la matriz
	for (size_t i = 0; i < varillas.size(); i++)
	{
		for (size_t j = 0; j <= L; j++) 
		{
			if (j == 0) { //caso base
				matriz[i][j] = 1;
			}
			else if (i == 0) { //otro caso baso
				matriz[i][j] = 0;
			}
			else if (varillas[i].longitud > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else{
				//matriz[i][j] = (matriz[i - 1][j] || matriz[i - 1][j - varillas[i].longitud]);
				matriz[i][j] = matriz[i - 1][j] + matriz[i - 1][j - varillas[i].longitud];
			}
		}
	}

	numFormas = matriz[varillas.size() - 1][L];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() 
{
    // leer los datos de la entrada
	int N, L;
	cin >> N >> L;
    if (! std::cin)
        return false;
    
	vector<Varilla> varillas_;
	for (size_t i = 0; i < N; i++)
	{
		int l, c;
		cin >> l >> c;

		varillas_.push_back({l, c});
	}

	int numFormas = 0;

	varillas(varillas_, L, numFormas);
    // escribir sol
	numFormas ? cout << "SI" << " " << numFormas : cout << "NO";
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