// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct User {
	int id, periodo_Actual, periodo;

	User(): id(-1), periodo(-1), periodo_Actual(-1) {};
	User(int id, int p) : id(id), periodo(p), periodo_Actual(p) {};
};

/*struct comp
{
	bool operator()(const User& u1, const User& u2) const {
		return u1.periodo < u2.periodo || (u1.periodo == u2.periodo && u1.id < u2.id);
	}
};*/

void resuelve(PriorityQueue<User>& pQueue, const int& K) {
	for (size_t i = 0; i < K; i++){
		if (!pQueue.empty()) {
			User user = pQueue.top();
			pQueue.pop();

			cout << user.id << endl;

			user.periodo_Actual += user.periodo;
			pQueue.push(user);
		}
	}

	cout << "----" << endl;
};

bool operator<(const User& u1, const User& u2) {
	return u1.periodo_Actual < u2.periodo_Actual || (u1.periodo_Actual == u2.periodo_Actual && u1.id < u2.id);
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;

    if (N == 0)
        return false;
    
	PriorityQueue<User> pQueue;

	for (size_t i = 0; i < N; i++){
		int id, p;
		cin >> id >> p;

		pQueue.push({ id, p });
	}

	int K;
	cin >> K;
    
    // escribir sol
	resuelve(pQueue, K);

    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
