#include <iostream>
#include <string>
#include "TreeMap_AVL.h"
#include <vector>
#include <queue>

#pragma once
class mapExt :
	public map<int, int>
{
private:
	struct TreeNodeExt: public TreeNode
	{
		int tam_i = 1; //almacena numero de nodos del hijo izquierdo + 1 
		TreeNodeExt(clave_valor const& e, Link i = nullptr, Link d = nullptr,
			int alt = 1) : TreeNode(e, i, d, alt){}
	};
protected:

	static void actualizaTam_I(TreeNodeExt* node) {
		node->tam_i = altura(node->iz) + 1;
	}
	
	virtual bool inserta(clave_valor const& cv, Link & a) {
		bool crece = map<int, int>::inserta(cv, a);
		if (crece) actualizaTam_I(static_cast<TreeNodeExt*>(a));
		return crece;
	}

	void inorder(std::vector<int>& v, Link& a) {
		if (a != nullptr) { //si a == nullptr --> caso base de la recursion
			inorder(v, a->iz);
			v.push_back(a->cv.clave);
			inorder(v, a->dr);
		}
	}

public:
	//depuracion
	int getTamI(int const& c) {
		return static_cast<TreeNodeExt*>(busca(c, raiz))->tam_i;
	}

	virtual bool insert(clave_valor const& cv) {
		return this->inserta(cv, raiz);
	}

	void recorridoInorder(std::vector<int>& v) {
		inorder(v,raiz);
	}
};

void resuelve(mapExt& tree, std::queue<int>& q);
void entrada();

int main() {
	entrada();
	return 0;
}

void entrada(){
	int n;
	std::cin >> n;

	while (n != 0) {
		mapExt tree;
		std::queue<int> q;

		int i = 0;
		while (i < n) { //claves del arbol

			int clave;
			std::cin >> clave;

			tree.insert(clave);

			i++;
		}

		int elementos_a_consultar;
		std::cin >> elementos_a_consultar;

		i = 0;
		while (i < elementos_a_consultar) { //numero de elementos que se quieren consultar
			int elem;
			std::cin >> elem;

			q.push(elem - 1);

			i++;
		}

		resuelve(tree, q);

		std::cin >> n;
	}
}

void resuelve(mapExt & tree, std::queue<int>& q){
	std::vector<int> v;
	tree.recorridoInorder(v);

	while (!q.empty()) {
		int elem = q.front();

		if (elem < v.size()) {
			std::cout << v[elem] << std::endl;
		}
		else {
			std::cout << "??" << std::endl;
		}

		q.pop();
	}

	std::cout << "----" << std::endl;
}

