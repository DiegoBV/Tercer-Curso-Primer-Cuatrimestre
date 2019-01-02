// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Grafo.h"

using namespace std;
class Amigos
{
private:
	int tam_comp_conexa_mas_grande;
	vector<bool> marcados;

	void dfs(const Grafo& g, int v, int& tam) {
		marcados[v] = true;
		tam++;

		for (int w : g.ady(v)) {
			if (!marcados[w]) {
				dfs(g, w, tam);
			}
		}
	};

public:
	Amigos(const Grafo& g): marcados(g.V(), false), tam_comp_conexa_mas_grande(0) {
		for (size_t i = 0; i < g.V(); i++){
			if (!marcados[i]) {
				int tam = 0;
				dfs(g, i, tam);
				tam_comp_conexa_mas_grande = max(tam_comp_conexa_mas_grande, tam);
			}
		}
	};

	~Amigos() {};

	inline const int solucion() { return tam_comp_conexa_mas_grande; };

};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int N, M;
	cin >> N >> M;

	Grafo g(N);

	for (size_t i = 0; i < M; i++){
		int A, B;
		cin >> A >> B;

		g.ponArista(A - 1, B - 1);
	}

	Amigos sol(g);
    // escribir sol
	cout << sol.solucion() << endl;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}