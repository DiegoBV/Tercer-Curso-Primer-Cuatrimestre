// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

int K;

struct Casilla
{
	int pos, to;
	Casilla(): pos(-1), to(-1) {};
	Casilla(int pos, int to = -1) : pos(pos), to(to) {};
};

class resuelve
{
private:
	vector<bool> marcados;
	vector<int> distTo;
	int numero_minimo;

	void bfs(const vector<Casilla>& tablero, const int V) {
		queue<int> q;
		distTo[V] = 0;
		marcados[V] = true;
		q.push(V);

		while (!q.empty()) {
			int father = q.front();
			q.pop();

			for (size_t i = father + 1; i <= father + K; i++){ //los adyacentes son los k siguientes
				if (i < tablero.size()) {
					if (!marcados[i]) {
						distTo[i] = distTo[father] + 1;
						marcados[i] = true;
						q.push(i);
			if (tablero[i].to != -1) { //tiene otro adyacente...
				if (!marcados[tablero[i].to]) {
					distTo[tablero[i].to] = distTo[father] + 1;
					marcados[tablero[i].to] = true;
					q.push(tablero[i].to);
				}
			}
					}
				}
			}

		}
	};

public:
	resuelve(const vector<Casilla>& tablero): marcados(tablero.size(), false), distTo(tablero.size(), 0), 
		numero_minimo(0){

		bfs(tablero, 1);

		numero_minimo = distTo[tablero.size() - 1];

	};
	~resuelve() {};

	inline const int getSol() { return numero_minimo; };

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, S, E;
	cin >> N >> K >> S >> E;

    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;
    
	vector<Casilla> tablero((N * N) + 1);
	tablero[0] = { -100, -100 };
	for (size_t i = 0; i < (S + E); i++){
		int in, f;
		cin >> in >> f;

		tablero[in] = { in, f };
	}
	resuelve sol(tablero);
    // escribir sol
	cout << sol.getSol() << endl;
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
