// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void resuelveCaso() {
	//priority_queue<int> mayores;
	//priority_queue<int, vector<int>, greater<int>> menores;

	int NumeroPilas, V;
	cin >> NumeroPilas >> V;
	vector<int> pilas;

	for (size_t i = 0; i < NumeroPilas; i++){
		int voltaje;
		cin >> voltaje;
		pilas.push_back(voltaje);
		//mayores.push(voltaje);
		//menores.push(voltaje);
	}

	sort(pilas.begin(), pilas.end());
	int numCoches = 0;
	int i = 0; int j = pilas.size() - 1;

	while (j > i) { //si no se cruzan
		if (pilas[i] + pilas[j] >= V) {
			numCoches++;
			j--;
		}

		i++;
	}
	
	/*int numCoches = 0;
	int i = 0; int j = NumeroPilas - 1;
	while (!mayores.empty() && !menores.empty() && j > i) {
		int el_mayor = mayores.top();
		int el_menor = menores.top();

		menores.pop();                //siempre se quita
		i++;

		if (el_mayor + el_menor >= V) {
			numCoches++; //se puede poner en funcionamiento otro coche
			mayores.pop();  //se pasa a comprobar el siguiente de mayor voltaje
			j--;
		}
	}*/
	cout << numCoches << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;

	for (int i = 0; i < numCasos; ++i) {
		resuelveCaso();
	}

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}