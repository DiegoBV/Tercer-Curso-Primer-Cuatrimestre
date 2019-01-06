// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<int, int>> direcciones = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
class cuenta_ovejas
{
private:
	vector<vector<bool>> marcados;
	int ovejas_blancas;
	bool es_correcta(const vector<vector<char>>& foto, const int i, const int j) {
		return (i >= 0 && i < foto.size() && j >= 0 && j < foto[0].size());
	};

	void dfs(const vector<vector<char>>& foto, const int i, const int j) {
		marcados[i][j] = true;

		//adyacencia
		for (size_t k = 0; k < direcciones.size(); k++) {
			int ni, nj;
			ni = i + direcciones[k].first;
			nj = j + direcciones[k].second;

			if (es_correcta(foto, ni, nj) && foto[ni][nj] == '.') {
				if (!marcados[ni][nj]) {
					dfs(foto, ni, nj);
				}
			}
		}
	};

public:
	cuenta_ovejas(const vector<vector<char>>& foto) : marcados(foto.size(), 
		vector<bool>(foto[0].size())), ovejas_blancas(-1) {
		
		for (size_t i = 0; i < foto.size(); i++){
			for (size_t j = 0; j < foto[i].size(); j++) {
				if (!marcados[i][j] &&  foto[i][j] == '.') {
					//componente conexa blanca, una es el fondo, si hay mas, son ovejas
					dfs(foto, i, j);
					ovejas_blancas++;
				}
			}
		}
	};

	~cuenta_ovejas() {};

	inline int getOvejasBlancas() const { return ovejas_blancas; };

};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int ANCHO, ALTO;
	cin >> ANCHO >> ALTO;

    if (!std::cin)
        return false;

	vector<vector<char>> foto(ALTO, vector<char>(ANCHO));
	for (size_t i = 0; i < ALTO; i++){
		for (size_t j = 0; j < ANCHO; j++) {
			char c;
			cin >> c;

			foto[i][j] = c;
		}
	}
    
	cuenta_ovejas sol(foto);
    // escribir sol
	cout << sol.getOvejasBlancas() << endl;
    
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