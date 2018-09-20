#pragma once
#include <vector>
#include "TreeMap_AVL.h"

template <class Clave, class Valor, class Comparador = std::less<Clave>>
class TreeMap_Rango :
	public map<Clave, Valor, Comparador>
{
private:

	void rango(std::vector<Clave>& v, Clave k1, Clave k2, map<Clave, Valor, Comparador>::Link root) {
		
		if (root == nullptr) {
			return;
		}

		if (root->cv.clave > k2) {
			rango(v, k1, k2, root->iz);
		}
		else if (root->cv.clave < k1) {
			rango(v, k1, k2, root->dr);
		}
		else{
		// (k1 < root->cv.valor < k2) {
			rango(v, k1, k2, root->iz);
			v.push_back(root->cv.clave);
			rango(v, k1, k2, root->dr);
		}
	}

public:
	TreeMap_Rango() {};
	virtual ~TreeMap_Rango() {};

	void calcularRango(std::vector<Clave>& v, Clave k1, Clave k2) {
		rango(v, k1, k2, map<Clave, Valor, Comparador>::raiz);
	}
};


