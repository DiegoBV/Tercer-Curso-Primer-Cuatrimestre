//DIEGO BARATTO VALDIVIA
#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include <vector>

using namespace std;

//struct del usuario con la informacion necesaria para el problema
struct User {
	int id_;
	int periodo_;
	int tInicial_;

	User(int id, int t) : id_(id), periodo_(t), tInicial_(t) {};
	User(): id_(0), periodo_(0), tInicial_(0) {};
};

//operador comparador
struct Comparador {
	bool operator()(const User& u1, const User& u2) const {
		return (u1.periodo_ < u2.periodo_) || (u1.periodo_ == u2.periodo_ && u1.id_ < u2.id_);
	}
};

//coste O(k), siendo k el numero de envios que se quieren comprobar
void resuelve(PriorityQueue<User, Comparador>& pQueue, const int& k) {
	for (int i = 0; i < k; i++) {
		//el top se saca del monticulo (el usuario con la prioridad mas alta --> periodo mas pequeño)
		User actual_user = pQueue.top(); 
		pQueue.pop();

		//se muestra por pantalla
		cout << actual_user.id_ << endl;

		//se introduce de nuevo en el monticulo con un nuevo periodo
		actual_user.periodo_ += actual_user.tInicial_;
		pQueue.push(actual_user);
	}

	cout << "----" << endl;
}
void entrada() {
	int n = 0;
	cin >> n;

	while (n != 0) {
		PriorityQueue<User, Comparador> pQueue;

		for (int i = 0; i < n; i++) {
			int id, periodo;
			cin >> id >> periodo;

			pQueue.push(User(id, periodo));
		}

		int k;
		cin >> k;

		resuelve(pQueue, k);

		cin >> n;
	}

}

int main() {
	entrada();
	return 0;
}