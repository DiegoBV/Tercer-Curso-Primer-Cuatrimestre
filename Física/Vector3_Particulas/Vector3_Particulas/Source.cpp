#include <iostream>
#include <string>
#include "Vector3.h"
#include "Particle.h"
using namespace std;

int main() {
	Vector3 v = Vector3(2, 0, 1);
	Vector3 g = Vector3(0, 0, 1);
	cout << v.x << " " << v.y << " " << v.z << " " << endl << endl;
	Particle p = Particle(v, g, g);
	p.integrate(0.1);
	cout << "Posicion de la particula A: " << p.p.x << " " << p.p.y << " " << p.p.z;
	system("pause");
	return 0;
}
