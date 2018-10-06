//DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
struct Instrumento { //struct con los datos de los diferentes tipos de instrumentos
	float musicos;
	float numPartituras;

	Instrumento(int m, int p = 1) : musicos(m), numPartituras(p) {};
	Instrumento() {}
};

//operador comparador
struct Comp
{
	bool operator()(const Instrumento& ins1, const Instrumento& ins2) const
	{
		return ceil(ins1.numPartituras / ins1.musicos < ins2.numPartituras / ins2.musicos);
		//return el valor redondeado hacia arriba para saber el numero maximo de musicos por atril
	}
};

//O(n) siendo n el numero de partituras
int resuelve_caso(PriorityQueue<Instrumento, Comp>& pQueue, int numPartituras) {
	numPartituras -= pQueue.size(); //repartes una partitura para cada uno de los músicos

	for (int i = 0; i < numPartituras; i++) {
		Instrumento aux = pQueue.top();
		pQueue.pop();

		aux.numPartituras++;

		pQueue.push(aux); // le damos al elemento mayor de todos los numeros un partitura
	}

	return ceil(pQueue.top().musicos / pQueue.top().numPartituras); //cuando se quede sin partituras, devuelve el elemento mayor, es decir, el mayor numero de musicos que comparten atril
}

bool entrada() {
	int p, n; //partituras y numero de instrumentos diferentes
	cin >> p >> n;

	PriorityQueue<Instrumento, Comp> pQueue;

	for (int i = 0; i < n; i++) {
		int newElement;
		cin >> newElement;

		Instrumento ins = Instrumento(newElement);

		pQueue.push(ins);
	}

	if (!cin) { 
		return false;
	}

	cout << resuelve_caso(pQueue, p) << endl;

	return true;
}
int main() {

	while (entrada());

	return 0;
}