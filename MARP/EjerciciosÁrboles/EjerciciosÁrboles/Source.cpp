#include "bintree_eda.h"
#include <iostream>
#include <string>

using namespace std;

int compruebaEquilibrio(const bintree<char>& a, bool& eq);
void resuelve(const bintree<char>& root);

int main() {

	int n; //numero de arboles a comprobar
	cin >> n;

	while (n > 0) {
		bintree<char> bitree;
		bitree = leerArbol('.');
		resuelve(bitree);
		n--;
	}

	//system("pause");
	return 0;
}

void resuelve(const bintree<char>& root) {
	bool eq = true; //bool que indica si esta o no equilibrado

	int h = compruebaEquilibrio(root, eq); //el metodo devuelve la altura del arbol

	//cout << h << endl; //salida de la altura del arbol

	eq == true ? (cout << "SI" << endl) : (cout << "NO" << endl); //salida especificada por el ejercicio
}
int compruebaEquilibrio(const bintree<char>& a, bool& eq) {
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