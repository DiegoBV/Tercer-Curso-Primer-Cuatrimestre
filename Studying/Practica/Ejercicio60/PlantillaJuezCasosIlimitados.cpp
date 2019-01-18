// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

bool esPosible(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<bool> matriz(n + 1, L + 1, false);

	matriz[0][0] = true;
	for (int i = 1; i <= n; i++) {
		matriz[i][0] = true;
		for (int j = 1; j <= L; j++) {
			if (varillas[i].first > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = (matriz[i - 1][j] || matriz[i - 1][j - varillas[i].first]);
			}
		}
	}

	return matriz[n][L];
};

bool esPosibleMejorado(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	vector<bool> matriz(L + 1, false);
	matriz[0] = true;

	for (int i = 1; i <= n; i++) {
		for (int j = L; j > 0; j--) {
			if (varillas[i].first > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = (matriz[j] || matriz[j - varillas[i].first]);
			}
		}
	}

	return matriz[L];
};

int numFormas(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> matriz(n + 1, L + 1, 0);

	matriz[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 1;
		for (int j = 1; j <= L; j++) {
			if (varillas[i].first > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = matriz[i - 1][j] + matriz[i - 1][j - varillas[i].first];
			}
		}
	}
	return matriz[n][L];
};

int numFormasMejorado(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	vector<int> matriz(L + 1, 0);
	matriz[0] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = L; j > 0; j--) {
			if (varillas[i].first > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = matriz[j] + matriz[j - varillas[i].first];
			}
		}
	}

	return matriz[L];
};

int numMinimo(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> matriz(n + 1, L + 1, 1001);

	matriz[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			if (varillas[i].first > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - varillas[i].first] + 1);
			}
		}
	}

	return matriz[n][L];
};

int numMinimoMejorado(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	vector<int> matriz(L + 1, 1E9);
	matriz[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = L; j > 0; j--) {
			if (varillas[i].first > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = min(matriz[j], matriz[j - varillas[i].first] + 1);
			}
		}
	}

	return matriz[L];
};

int costeMinimo(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> matriz(n + 1, L + 1, 1001);

	matriz[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			if (varillas[i].first > j) {
				matriz[i][j] = matriz[i - 1][j];
			}
			else {
				matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - varillas[i].first] + varillas[i].second);
			}
		}
	}

	return matriz[n][L];
};

int costeMinimoMejorado(const vector<pair<int, int>>& varillas, const int& L) {
	int n = varillas.size() - 1;
	vector<int> matriz(L + 1, 1E9);
	matriz[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = L; j > 0; j--) {
			if (varillas[i].first > j) {
				matriz[j] = matriz[j];
			}
			else {
				matriz[j] = min(matriz[j], matriz[j - varillas[i].first] + varillas[i].second);
			}
		}
	}

	return matriz[L];
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, L;
	cin >> N >> L;
    if (!std::cin)
        return false;
	vector<pair<int, int>> varillas;
	varillas.push_back({ -1, -1 });
	for (size_t i = 0; i < N; i++){
		int longi, coste;
		cin >> longi >> coste;

		varillas.push_back({ longi, coste });
	}

	bool sePuede = esPosibleMejorado(varillas, L);
	sePuede ? cout << "SI" << " " : cout << "NO";
	if (sePuede) {
		int numFormas_ = numFormasMejorado(varillas, L);
		cout << numFormas_ << " ";
		int min_ = numMinimoMejorado(varillas, L);
		cout << min_ << " ";
		int costeMini = costeMinimoMejorado(varillas, L);
		cout << costeMini;
	}
	cout << endl;
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