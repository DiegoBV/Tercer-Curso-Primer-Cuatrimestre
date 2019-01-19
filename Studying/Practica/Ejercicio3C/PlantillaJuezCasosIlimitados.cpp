// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;
vector<int> tiempo_isla;
class resuelve
{
private:
	vector<int> distTo;
	vector<int> distTo_keys;
	vector<int> edgeTo;
	vector<int> edgeTo_keys;
	IndexPQ<int> pq;
	bool se_puede;
	int distancia_total;

	void relax(AristaDirigida<int>& e, vector<int>& dist, vector<int>& edge) {
		int v = e.from(), w = e.to();
		if (dist[w] > dist[v] + e.valor()) {
			dist[w] = dist[v] + e.valor();
			edge[w] = e.from();
			pq.update(w, dist[w]);
		}
	};

	void dijkstra(const GrafoDirigidoValorado<int>& g, vector<int>& dist, vector<int>& edge,const int ORIGEN) {

		dist[ORIGEN] = 0;
		pq.push(ORIGEN, 0);

		while (!pq.empty()){
			int v = pq.top().elem;
			pq.pop();

			for (AristaDirigida<int> e : g.ady(v)) {
				relax(e, dist, edge);
			}
		}
	};

public:
	resuelve(const GrafoDirigidoValorado<int>& g, const vector<int>& tiempo_isla,
		const vector<int>& llaves, const int INICIO, const int OLIMPO): 
			distTo(g.V(), numeric_limits<int>::max()), distTo_keys(g.V(), numeric_limits<int>::max()), 
				pq(g.V()), distancia_total(0), se_puede(true), edgeTo(g.V()), edgeTo_keys(g.V()) {

		dijkstra(g, distTo, edgeTo, INICIO); //distancia desde el inicio a todas las llaves

		GrafoDirigidoValorado<int> g_inverso = g.inverso();

		pq = IndexPQ<int>(g.V());
		dijkstra(g_inverso, distTo_keys, edgeTo_keys, OLIMPO);  //distancia desde todas las llaves hasta el OLIMPO

		int min_ = numeric_limits<int>::max();

		for (int i = 0; i < llaves.size(); i++) {
			if (distTo[llaves[i]] == numeric_limits<int>::max() || distTo_keys[llaves[i]] == numeric_limits<int>::max()) {
				se_puede = false;
			}
			int sumaDistancias = distTo[llaves[i]] + distTo_keys[llaves[i]] + tiempo_isla[OLIMPO];
			
			min_ = min(min_, sumaDistancias); //minima distancia que hay que recorrer para pillar 
			//una llave, recorrer la isla donde se encuentra la llave e ir al olimpo
		}

		if (se_puede) {
			cout << min_ << " ";
			distTo = vector<int>(g.V(), numeric_limits<int>::max());
			edgeTo = vector<int>(g.V());
			pq = IndexPQ<int>(g.V());

			dijkstra(g, distTo, edgeTo, OLIMPO); //da la distancia desde todos los puntos hasta el inicio

			int o_distance = distTo[INICIO] + tiempo_isla[INICIO];

			if (o_distance == numeric_limits<int>::max()) {
				se_puede = false;
			}
			else {
				distancia_total = o_distance + min_;
				cout << o_distance << " ";
				cout << o_distance + min_ << endl;
			}
		}
	};

	~resuelve() {};

	inline const int getSol() { return distancia_total; };

	inline const bool sePuede() { return se_puede; };

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int I, N, L, INICIO, OLIMPO;
	cin >> I >> N >> L >> INICIO >> OLIMPO;
    if (!std::cin)
        return false;

	GrafoDirigidoValorado<int> g(I);
	
	tiempo_isla.clear();
	for (size_t i = 0; i < I; i++){
		int time;
		cin >> time;

		tiempo_isla.push_back(time);
	}

	for (size_t i = 0; i < N; i++){
		int isla1, isla2, tiempo;
		cin >> isla1 >> isla2 >> tiempo;

		g.ponArista({ isla1 - 1, isla2 - 1, tiempo + tiempo_isla[isla1 - 1]});
	}

	vector<int> llaves;
	for (size_t i = 0; i < L; i++){
		int isla;
		cin >> isla;

		llaves.push_back(isla - 1);
	}
    
	resuelve sol(g, tiempo_isla, llaves, INICIO - 1, OLIMPO - 1);
    // escribir sol
	if (!sol.sePuede()) {
		cout << "Rescate imposible" << endl;
	}
    
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