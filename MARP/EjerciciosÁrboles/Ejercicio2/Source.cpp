#include "bintree_eda.h"
#include <iostream>
#include <string>

using namespace std;

int compruebaEquilibrio(const bintree<int>& a, bool& eq);
void resuelve(const bintree<int>& root);
bool compruebaBusqueda(const bintree<int>& root, const bintree<int>& left, const bintree<int>& right);

int main() {

	int n; //numero de arboles a comprobar
	cin >> n;

	while (n > 0) {
		bintree<int> bitree;
		bitree = leerArbol(-1);
		resuelve(bitree);
		n--;
	}

	//system("pause");
	return 0;
}

void resuelve(const bintree<int>& root) {
	bool eq = true; //bool que indica si esta o no equilibrado

	int h = compruebaEquilibrio(root, eq); //el metodo devuelve la altura del arbol

										  //cout << h << endl; //salida de la altura del arbol

	eq && compruebaBusqueda(root, bintree<int>(), bintree<int>()) ? (cout << "SI" << endl) : (cout << "NO" << endl); //salida especificada por el ejercicio
}
int compruebaEquilibrio(const bintree<int>& a, bool& eq) {
	if (!a.empty()) { //si el arbol no esta vacio

		int h1 = compruebaEquilibrio(a.left(), eq); //calcula su altura por la izquierda
		int h2 = compruebaEquilibrio(a.right(), eq); //calcula su altura por la derecha

		if (abs(h1 - h2) >= 2) { //si la diferencia entre ambas alturas es mayor o igual que dos, esta desequilibrado
			eq = false;
			//se podria detener la ejecucion aqui (?)
		}

		return max(h1, h2) + 1; //return del maximo entre las alturas izquierda y derecha (+1)
	}
	else { // si nos encontramos en el caso de arbol vacio
		return 0; //altura = 0
	}
}

/*int maxValor(const bintree<int>& root) {
	if (root.empty()) {
		return -1000;
	}

	return maximo(root.root(), maxValor(root.left()), maxValor(root.right()));
}

int minValor(const bintree<int>& root)
{
	if (root.empty()) {
		return 1000;
	}

	return minimo(root.root(), minValor(root.left()), minValor(root.right()));
}*/

bool compruebaBusqueda(const bintree<int>& root, const bintree<int>& min, const bintree<int>& max) {

	if (root.empty()) { //si es vacio, caso base
		return true;
	}

	if (!min.empty() && root.root() <= min.root()) { //si se cumple que root es menor que min --> false
		return false;
	}

	if (!max.empty() && root.root() >= max.root()) { // si se cumple que root es mayor que el valor maximo ---> false
		return false;
	}
	
	bool l = compruebaBusqueda(root.left(), min, root); //recursion izquierda, root es ahora el hijo izquierdo, min es min 
	//y max es ahora el valor del padre

	bool r = compruebaBusqueda(root.right(), root, max); //recursion derecha, root es ahora el hijo derecho, min es el valor
	//del padre y max es max

	return l && r;
			
}

