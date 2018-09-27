#include "PriorityQueue.h"
#include <iostream>
#include <string>
using namespace std;

void entrada();
long long int resuelve(PriorityQueue<long long int>& pQueue);

int main() {
	entrada();
	return 0;
}

void entrada(){
	int n; //numero de elementos
	cin >> n;

	while (n != 0)
	{
		PriorityQueue<long long int> pQueue;
		
		int i = 0;
		while (i < n) {
			int elemento;
			cin >> elemento;
			pQueue.push(elemento);
			i++;
		}

		cout << resuelve(pQueue) << endl;
		cin >> n;
	}
}

long long int resuelve(PriorityQueue<long long int>& pQueue){
	long long int esfuerzo_minimo = 0;
	
	bool stop = false;

	while (pQueue.size() != 1) {
		long long int suma = 0;
		suma += pQueue.top();
		pQueue.pop();
		suma += pQueue.top();
		pQueue.pop();

		esfuerzo_minimo += suma;

		pQueue.push(suma);
	}

	return esfuerzo_minimo;
}