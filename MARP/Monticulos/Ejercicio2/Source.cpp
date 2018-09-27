//DIEGO BARATTO VALDIVIA
#include "PriorityQueue.h"
#include <iostream>
#include <string>

using namespace std;

//struct del usuario con la informacion necesaria para el problema
struct User
{
	int id_;
	int periodoActual_;
	int periodoInicial_;

	User() : id_(0), periodoActual_(0), periodoInicial_(0) {};
	User(int id, int periodoInicial) : id_(id), periodoActual_(periodoInicial), periodoInicial_(periodoInicial) {};
};

//operador comparador
struct Comp
{
	bool operator()(const User& user1, const User& user2) const
	{
		if (user1.periodoActual_ < user2.periodoActual_) {
			return true;
		}
		else if (user1.periodoActual_ == user2.periodoActual_) {
			if (user1.id_ < user2.id_) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	
	}
};

//coste O(k), siendo k el numero de envios que se quieren comprobar
void resuelve(PriorityQueue<User, Comp>& pQueue, const int& k) {
	for (int i = 0; i < k; i++) {
		//el top se saca del monticulo (el usuario con la prioridad mas alta --> periodo mas pequeño)
		User usuario = pQueue.top();
		pQueue.pop();

		//se muestra por pantalla
		cout << usuario.id_ << endl;

		//se introduce de nuevo en el monticulo con un nuevo periodo
		usuario.periodoActual_ += usuario.periodoInicial_;
		pQueue.push(usuario);
	}

	cout << "----" << endl;
}

void entrada() {
	int n = 0;
	cin >> n;

	while (n != 0) {
		PriorityQueue<User, Comp> pQueue;

		for (int i = 0; i < n; i++) {
			int id, periodo;
			cin >> id >> periodo;

			pQueue.push(User(id, periodo));
		}

		int k = 0;
		cin >> k;

		resuelve(pQueue, k);

		cin >> n;
	}
}

int main() {
	entrada();
	return 0;
}