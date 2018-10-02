//DIEGO BARATTO VALDIVIA
#include "PriorityQueue.h"
#include <iostream>
#include <string>

using namespace std;

struct Tarea {
	int tiempo_comienzo;
	int tiempo_finalizacion;
	int periodo_; //si es periodica --> periodo != -1

	Tarea() : tiempo_comienzo(0), tiempo_finalizacion(0), periodo_(-1) {};
	Tarea(int tiempoComienzo, int tiempoFin, int periodo = -1): tiempo_comienzo(tiempoComienzo), tiempo_finalizacion(tiempoFin), periodo_(periodo) {}
};

//operador comparador
struct Comp
{
	bool operator()(const Tarea& tarea1, const Tarea& tarea2) const
	{
		return tarea1.tiempo_comienzo < tarea2.tiempo_comienzo;
	}
};

bool resuelveCaso(PriorityQueue<Tarea, Comp>& pQueue, const int& t) {
	bool hay_conflicto = false;
	bool tiempo_acabado = false;

	Tarea tareaAnterior = Tarea(-1, -1);

	while (!pQueue.empty() && !hay_conflicto && !tiempo_acabado) {
		Tarea tareaActual = pQueue.top();
		pQueue.pop();

		if (tareaActual.tiempo_comienzo >= t) { //si la tarea siguiente esta fuera de rango ya no se comprueba [0, t)
			tiempo_acabado = true;
		}
		else if (tareaAnterior.tiempo_comienzo <= tareaActual.tiempo_comienzo &&  tareaActual.tiempo_comienzo < tareaAnterior.tiempo_finalizacion) { //esto significa que la tarea siguiente esta en medio del intervalo de la tarea anterior
			hay_conflicto = true;
		}
		else if(tareaActual.periodo_ != -1){ //si no hay conflicto, se comprueba si la tarea es periodica, si lo es, se vuelve a añadir con sus tiempos correspondientes, si no, no hace nada
			pQueue.push(Tarea(tareaActual.tiempo_comienzo + tareaActual.periodo_, tareaActual.tiempo_finalizacion + tareaActual.periodo_, tareaActual.periodo_));
		}

		tareaAnterior = tareaActual; //la tarea anterior se convierte en la actual en la siguiente vuelta
	}

	return hay_conflicto;
}

bool entrada() {

	PriorityQueue<Tarea, Comp> pQueue;

	int n; //numero de tareas unicas
	cin >> n;

	int m; //numero de tareas periodicas
	cin >> m;

	int t; //intervalo de tiempo a consultar --> [0, t)
	cin >> t;

	for (int i = 0; i < n; i++) { //tareas unicas
		int tC, tF;
		cin >> tC >> tF;

		pQueue.push(Tarea(tC, tF));
	}

	for (int j = 0; j < m; j++) { //tareas periodicas
		int tC, tF, periodo;
		cin >> tC >> tF >> periodo;

		pQueue.push(Tarea(tC, tF, periodo));
	}

	if (!cin) { //creo que aqui hay un fallo dunno
		return false;
	}

	resuelveCaso(pQueue, t) ? cout << "SI" : cout << "NO";
	cout << endl;

	return true;
}

int main() {
	while (entrada());
	return 0;
}