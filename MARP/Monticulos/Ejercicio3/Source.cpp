//DIEGO BARATTO VALDIVIA
#include "PriorityQueue.h"
#include <iostream>
#include <string>

using namespace std;

//struct de los pacientes
struct Paciente{
	int gravedad_;
	int prioridad_por_tiempo_; //a menor prioridad por tiempo, mas tiempo lleva esperando, más prioridad por atenderle
	string nombre_;

	Paciente() {};
	Paciente(string name, int gravedad, int pt) : nombre_(name), gravedad_(gravedad), prioridad_por_tiempo_(pt) {};
};

//operador comparador
struct Comp
{
	bool operator()(const Paciente& paciente1, const Paciente& paciente2) const
	{
		if (paciente1.gravedad_ > paciente2.gravedad_) {
			return true;
		}
		else if (paciente1.gravedad_ == paciente2.gravedad_) {
			if (paciente1.prioridad_por_tiempo_ < paciente2.prioridad_por_tiempo_) {
				return true;
			}
		}
		return false;
	}
};

//Coste O(n), siendo n el numero de elementos del vector
void resuelve(vector<Paciente>& pacientesAtendidos) {
	for (Paciente p : pacientesAtendidos) {
		cout << p.nombre_ << endl;
	}
	cout << "----" << endl;
}

void entrada() {
	int n;

	cin >> n;

	while (n != 0) {
		PriorityQueue<Paciente, Comp> pQueue;
		vector<Paciente> pacientesAtendidos;

		for (int i = 0; i < n; i++) {
			char event_type;
			cin >> event_type;
			
			if (event_type == 'I') {
				string name;
				int gravedad;

				cin >> name >> gravedad;

				pQueue.push(Paciente(name, gravedad, i));
			}
			else if (event_type == 'A') {
				pacientesAtendidos.push_back(pQueue.top()); //saber el paciente que necesita ser atendido tiene un coste 0(1)
				pQueue.pop();
			}
		}

		resuelve(pacientesAtendidos);

		cin >> n;
	}
}

int main(){
	entrada();
	return 0;
}