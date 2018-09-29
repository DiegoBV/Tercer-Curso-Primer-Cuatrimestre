//DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include <algorithm>
#include <vector>

using namespace std;

void resuelve(PriorityQueue<int> pQueue, vector<int>& solucion) { //necesito una copia...

	vector<int> v;

	//coste O(n) siendo n el numero de elementos del montículo
	while (!pQueue.empty()) {
		v.push_back(pQueue.top());
		pQueue.pop();
	}

	if (v.size() % 2 == 0) {
		int n1, n2;
		n1 = v.size() / 2;
		n2 = v.size() / 2 + 1;

		int mediana = (v[n1 - 1] + v[n2 - 1]); // /2

		solucion.push_back(mediana);
	}
	else {
		int n1 = (v.size() + 1) / 2;

		int mediana = v[n1 - 1];

		solucion.push_back(mediana * 2);
	}
}

void entrada() {
	int n;
	cin >> n;

	while (n != 0) {
		PriorityQueue<int> pQueue;
		vector<int> solucion;

		for (int i = 0; i < n; i++) {
			int elem;
			cin >> elem;

			pQueue.push(elem);

			resuelve(pQueue, solucion);
		}

		for (int i : solucion) {
			cout << i << " ";
		}

		cout << endl;
		cin >> n;
	}
}
int main() {
	entrada();
	return 0;
}