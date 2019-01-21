// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> dirs = { {0, 1},{0, -1},{1, 0},{-1, 0} };

class manchas_negra
{
private:
	vector<vector<bool>> marcados;
	int numeroManchas;
	int manchaGrande;

	bool esCorrecta(const vector<vector<char>>& bitmap, const int& i, const int& j) {
		return (i >= 0 && i < bitmap.size() && j >= 0 && j < bitmap[0].size());
	};

	void dfs(const vector<vector<char>>& bitmap, const int& i, const int& j, int& numeroPixeles) {
		marcados[i][j] = true;
		numeroPixeles++;

		for (pair<int, int> dir : dirs) {
			int ni = i + dir.first;
			int nj = j + dir.second;

			if (esCorrecta(bitmap, ni, nj) && bitmap[ni][nj] == '#') {
				if (!marcados[ni][nj]) {
					dfs(bitmap, ni, nj, numeroPixeles);
				}
			}
		}
	};

public:
	manchas_negra(const vector<vector<char>>& bitmap) : marcados(bitmap.size(),
		vector<bool>(bitmap[0].size())), numeroManchas(0), manchaGrande(0) {
		for (size_t i = 0; i < bitmap.size(); i++) {
			for (size_t j = 0; j < bitmap[i].size(); j++) {
				if (!marcados[i][j] && bitmap[i][j] == '#') {
					numeroManchas++;
					int numeroPixeles = 0;
					dfs(bitmap, i, j, numeroPixeles);
					manchaGrande = max(manchaGrande, numeroPixeles);
				}
			}
		}
	};

	~manchas_negra() {};

	inline const int getNumeroManchas() { return numeroManchas; };
	inline const int getManchaGrande() { return manchaGrande; };

};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int F, C;
	cin >> F >> C;
    if (!std::cin)
        return false;
	vector<vector<char>> bitmap(F, vector<char>(C));
	for (size_t i = 0; i < F; i++){
		for (size_t j = 0; j < C; j++) {
			char pixel;
			cin >> pixel;

			bitmap[i][j] = pixel;
		}
	}
    
	manchas_negra sol(bitmap);
    // escribir sol
	cout << sol.getNumeroManchas() << " " << sol.getManchaGrande() << endl;
    
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