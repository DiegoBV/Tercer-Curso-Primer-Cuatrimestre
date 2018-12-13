// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
#include <vector>
#include"Matriz.h"

using namespace std;

struct Varilla
{
	int longitud, coste;

	Varilla() {};
	Varilla(int l, int c) : longitud(l), coste(c) {};
};

void varillasBool(vector<Varilla>& varillas, int L, bool& sePuede) {
	Matriz<bool> matriz(varillas.size(), L + 1, 0);

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
			else {
				matriz[i][j] = (matriz[i - 1][j] || matriz[i - 1][j - varillas[i].longitud]);
			}
		}
	}

	sePuede = matriz[varillas.size() - 1][L];
};

void varillasBool2(vector<Varilla>& varillas, int L, bool& sePuede) {
	int n = varillas.size() - 1;

	vector<bool> matriz(L + 1, false);

	//rellenar la matriz
	matriz[0] = true;
	for (size_t i = 1; i <= n; i++){
		for (size_t j = L; j > 0; j--) {
			if (varillas[i].longitud > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = (matriz[j] || matriz[j - varillas[i].longitud]);
			}
		}
	}

	sePuede = matriz[L];
};

void varillasNumeroFormas(vector<Varilla>& varillas, int L, int& numFormas) 
{
	int n = varillas.size() - 1;
	Matriz<int> matriz(varillas.size(), L + 1, 0);

	matriz[0][0] = 1;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		matriz[i][0] = 1;
		for (size_t j = 1; j <= L; j++) 
		{
			if (varillas[i].longitud > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else{
				matriz[i][j] = matriz[i - 1][j] + matriz[i - 1][j - varillas[i].longitud];
			}
		}
	}

	numFormas = matriz[n][L];
};

void varillasNumeroFormas2(vector<Varilla>& varillas, int L, int& numFormas) {
	int n = varillas.size() - 1;

	vector<int> matriz(L + 1, 0);

	matriz[0] = 1;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = L; j > 0; j--) {
			if (varillas[i].longitud > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = matriz[j] + matriz[j - varillas[i].longitud];
			}
		}
	}

	numFormas = matriz[L];
}

void varillasMinimoNumero(vector<Varilla>& varillas, int L, int& minNum)
{
	int n = varillas.size() - 1;
	Matriz<int> matriz(varillas.size(), L + 1, 1001);

	matriz[0][0] = 0;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		matriz[i][0] = 0;
		for (size_t j = 1; j <= L; j++)
		{
			if (varillas[i].longitud > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - varillas[i].longitud] + 1);
			}
		}
	}

	minNum = matriz[n][L]; //??
};

void varillasMinimoNumero2(vector<Varilla>& varillas, int L, int& minNum) {
	int n = varillas.size() - 1;

	vector<int> matriz(L + 1, 1001);

	matriz[0] = 0;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = L; j > 0; j--) {
			if (varillas[i].longitud > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = min(matriz[j], matriz[j - varillas[i].longitud] + 1);
			}
		}
	}

	minNum = matriz[L];
};

void varillasMinimoCoste(vector<Varilla>& varillas, int L, int& minCoste)
{
	int n = varillas.size() - 1;
	Matriz<int> matriz(varillas.size(), L + 1, 1E9); //1E9

	matriz[0][0] = 0;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		matriz[i][0] = 0;
		for (size_t j = 1; j <= L; j++)
		{
			if (varillas[i].longitud > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - varillas[i].longitud] + varillas[i].coste);
			}
		}
	}

	minCoste = matriz[n][L]; //??
};

void varillasMinimoCoste2(vector<Varilla>& varillas, int L, int& minCoste) {
	int n = varillas.size() - 1;

	vector<int> matriz(L + 1, 1E9);

	matriz[0] = 0;
	//rellenar la matriz
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = L; j > 0; j--) {
			if (varillas[i].longitud > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = min(matriz[j], matriz[j - varillas[i].longitud] + varillas[i].coste);
			}
		}
	}

	minCoste = matriz[L];
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
    
	vector<Varilla> varillas_(N + 1); //importante empezar en el 1...
	for (size_t i = 1; i <= N; i++)
	{
		int l, c;
		cin >> l >> c;

		varillas_[i] = {l, c};
	}

	int numFormas = 0;
	int minNum = 0;
	int minCoste = 0;
	bool sePuede = false;
	varillasBool2(varillas_, L, sePuede);
	varillasNumeroFormas2(varillas_, L, numFormas);
	varillasMinimoNumero2(varillas_, L, minNum);
	varillasMinimoCoste2(varillas_, L, minCoste);
    // escribir sol
	sePuede ? cout << "SI" << " " << numFormas << " " << minNum << " " << minCoste : cout << "NO";
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