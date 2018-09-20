// DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include <vector>
#include "TreeMap_AVL.h"

#pragma once
class TreeMap_Rango :
	public map<int, int>
{
private:

	void rango(std::vector<int>& v, int k1, int k2, map<int, int>::Link root) { //duncion recursiva que calcula los numeros en un rango

		if (root == nullptr) { //si es vacio -> caso base, no hace nada
			return;
		}

		if (root->cv.clave > k2) { //si el valor de la raiz es mayor que el limite superior del rango, solo puede buscar por la izquierda
			rango(v, k1, k2, root->iz);
		}
		else if (root->cv.clave < k1) { //si el valor de la raiz es menor que el limite inferior del rango, solo puede buscar por la derecha
			rango(v, k1, k2, root->dr);
		}
		else { //si el elemento esta entre medias, es decir, se encuentra en el rango
			rango(v, k1, k2, root->iz); //recursion por la izquierda
			v.push_back(root->cv.clave); //push de la clave ---> elementos ordenados
			rango(v, k1, k2, root->dr); //recursion por la derecha
		}
	}

public:
	TreeMap_Rango() {};
	virtual ~TreeMap_Rango() {};

	void calcularRango(std::vector<int>& v, int k1, int k2) {
		rango(v, k1, k2, map<int, int>::raiz);
	}
};

void resuelve(TreeMap_Rango& bstRange, std::vector<int> vSolucion, int k1, int k2) {

	bstRange.calcularRango(vSolucion, k1, k2); //calcula el rango

	for (int i : vSolucion) {
		std::cout << i << " "; //salida
	}

	std::cout << std::endl;
}

void entrada() {
	int n;
	std::cin >> n;

	while (n != 0) { //si n = 0, finaliza el programa
		int i = 0;
		TreeMap_Rango bstRange;
		std::vector<int> vSolucion;

		while (i < n) {

			int clave; 

			std::cin >> clave;
			bstRange.insert(clave); //inserta las claves en el bst

			i++;
		}

		int k1, k2;
		std::cin >> k1 >> k2; //rango

		resuelve(bstRange, vSolucion, k1, k2);
		
		std::cin >> n;
	}

}
int main() {

	entrada();
	return 0;
}