//DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include <algorithm>
#include <vector>

using namespace std;
//operador comparador
struct Comp
{
	bool operator()(const int& k1, const int& k2) const
	{
		return k1 > k2;
	}
};


//Coste O(1)
void resuelve(PriorityQueue<int>& minHeap, PriorityQueue<int, Comp>& maxHeap, int& current_Median) {

	//equilibra ambos monticulos para que su diferencia de tamaños sea, como minimo, 1
	if(abs(minHeap.size() - maxHeap.size()) > 1){
		if (minHeap.size() > maxHeap.size()) {
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
		else {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		}
	}
	
	//equilibrados
	if (minHeap.size() > maxHeap.size()){ //si el min tiene un elemento mas que el max, la mediana esta en el min
		current_Median = minHeap.top() * 2;
	}
	else if (maxHeap.size() > minHeap.size()) { //viceversa
		current_Median = maxHeap.top() * 2;
	}
	else { //son iguales, la media de ambos
		current_Median = (maxHeap.top() + minHeap.top()); // /2
	}
}

void entrada() {
	int n;
	cin >> n;

	while (n != 0) {
		PriorityQueue<int> minHeap;
		PriorityQueue<int, Comp> maxHeap;

		vector<int> solucion;
		int current_Median;

		int elem;
		cin >> elem;

		maxHeap.push(elem);
		resuelve(minHeap, maxHeap, current_Median);
		solucion.push_back(current_Median);

		for (int i = 1; i < n; i++) {
			
			int elem;
			cin >> elem;

			if (elem > current_Median/2) {
				minHeap.push(elem);
			}
			else {
				maxHeap.push(elem);
			}

			resuelve(minHeap, maxHeap, current_Median);
			solucion.push_back(current_Median);
		}

		//Mostrar solucion
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