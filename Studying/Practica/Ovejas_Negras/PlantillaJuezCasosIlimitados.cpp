// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

vector <pair<int, int>> dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

class ovejas_blancas
{
private:
	vector<vector<bool>> marcados;
	int numeroOvejasBlancas;

	bool esCorrecta(const vector<vector<char>>& foto, const int& i, const int& j) {
		return (i >= 0 && i < foto.size() && j >= 0 && j < foto[0].size());
	};

	void dfs(const vector<vector<char>>& foto, const int& i, const int& j) {
		marcados[i][j] = true;

		//adyacencia
		for (pair<int, int> dir : dirs) {
			int ni = i + dir.first, nj = j + dir.second;

			if (esCorrecta(foto, ni, nj) && foto[ni][nj] == '.') {
				if (!marcados[ni][nj]) {
					dfs(foto, ni, nj);
				}
			}
		}
	};

public:
	ovejas_blancas(const vector<vector<char>>& foto): marcados(foto.size(), 
		vector<bool>(foto[0].size())), numeroOvejasBlancas(-1) {
		for (int i = 0; i < foto.size(); i++) {
			for (int j = 0; j < foto[i].size(); j++) {
				if (!marcados[i][j] && foto[i][j] == '.') {
					dfs(foto, i, j);
					numeroOvejasBlancas++;
				}
			}
		}
	};

	~ovejas_blancas() {};

	inline const int getSol() { return numeroOvejasBlancas; };
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int ancho, alto;
	cin >> ancho >> alto;
    if (!std::cin)
        return false;

	vector<vector<char>> foto(alto, vector<char>(ancho));
	for (int i = 0; i < alto; i++) {
		for (int j = 0; j < ancho; j++) {
			char c;
			cin >> c;
			foto[i][j] = c;
		}
	}

	ovejas_blancas sol(foto);

	cout << sol.getSol() << endl;
    
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