// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
struct Actividad
{
	int tc, tf;

	Actividad() : tc(0), tf(0) {};
	Actividad(int tc, int tf) : tc(tc), tf(tf) {};
};

bool operator <(const Actividad& a1, const Actividad& a2) { return a1.tc < a2.tc; }; //antes era a1.tf > a2.tf

int resuelve(priority_queue<Actividad>& actividades) {
	int numCompanyeros = 0;
	//int temp = 0;
	int buffer_personas_libres = 0;

	Actividad a = actividades.top();
	actividades.pop();

	while (!actividades.empty()) {
		Actividad act = actividades.top();
		actividades.pop();

		if ((a.tc >= act.tc && a.tc < act.tf) || (a.tf > act.tc && a.tf < act.tf)) { //se solapan
			/*temp++;
			if(temp > numCompanyeros)
				numCompanyeros = temp;*/
			buffer_personas_libres--;
			if (buffer_personas_libres < 0) {
				numCompanyeros = buffer_personas_libres * -1;
			}
		}
		else {
			//si no se solapan
			/*a = act;
			temp = 0; //todos los antiguos companyeros han acabado sus tareas*/
			a = act;
			buffer_personas_libres = numCompanyeros /*-1*/;
		}
	}

	return numCompanyeros;
};

bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	cin >> N;
    if (N == 0)
        return false;

	priority_queue<Actividad> actividades;
	for (size_t i = 0; i < N; i++){
		int tCom, tFin;

		cin >> tCom >> tFin;
		actividades.push(Actividad(tCom, tFin));
	}
    // escribir sol
	cout << resuelve(actividades) << endl;
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
