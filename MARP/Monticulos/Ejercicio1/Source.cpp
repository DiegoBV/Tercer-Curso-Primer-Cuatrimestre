//DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

//Coste O(n), donde n es igual al numero de elementos del monticulo
long long int resuelve(PriorityQueue<long long int>& pQueue) {
	long long int suma_ = 0, esfuerzo_ = 0;

	while (pQueue.size() != 1) {
		long long int sumando1 = 0, sumando2 = 0;

		sumando1 = pQueue.top(); //saca el primer sumando
		pQueue.pop();
		sumando2 = pQueue.top(); //saca el segundo sumando
		pQueue.pop();

		suma_ = sumando1 + sumando2; //los suma
		esfuerzo_ += suma_; //calculo del esfuerzo

		pQueue.push(suma_); //push de la variable suma_ en el monticulo
	}

	return esfuerzo_;
}

void entrada() {
	int n = 0; 
	cin >> n;

	while (n != 0) {
		PriorityQueue<long long int> pQueue;

		for (int i = 0; i < n; i++) {
			long long int elem = 0;
			cin >> elem;

			pQueue.push(elem);
		}

		cout << resuelve(pQueue) << endl;

		cin >> n;
	}
}

int main() {
	entrada();
	return 0;
}