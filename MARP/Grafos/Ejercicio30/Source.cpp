//DIEGO BARATTO VALDIVIA
#include "Grafo.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class maxComponenteConexa {
private:
	vector<bool> marcados;
	int max_;
	//recorrido en profundidad, coste O(V + E)
	void calculaMax(const Grafo& g, int v, int& tam) {
		marcados[v] = true;
		tam++;
		for (int i : g.ady(v)) {
			if (!marcados[i]) { //si no lo hemos visitado
				calculaMax(g, i, tam);
			}
		}
	};
public:
	maxComponenteConexa() {};
	maxComponenteConexa(const Grafo& g) : max_(0), marcados(g.V(), false) {
		
		for (int i = 0; i < g.V(); i++) {
			if (!marcados[i]) { //si no está marcado, se recorre una nueva componente conexa
				int temp = 0;
				calculaMax(g, i, temp);
				max_ = max(max_, temp);
			}
		}
	};
	~maxComponenteConexa() {};

	inline int getTam() const { return max_; };
};

void entrada() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int numVertices;
		cin >> numVertices;
		Grafo g = Grafo(numVertices);

		int numAristas;
		cin >> numAristas;

		for (int j = 0; j < numAristas; j++) {
			int a, b; //personas que son amigos entre ellos
			cin >> a >> b;

			g.ponArista(a - 1, b - 1);
		}

		maxComponenteConexa sol(g);

		cout << sol.getTam() << endl;
	}
}

int main() {
	entrada();
	return 0;
}