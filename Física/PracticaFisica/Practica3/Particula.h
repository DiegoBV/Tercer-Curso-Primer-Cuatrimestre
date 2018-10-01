#include "RenderUtils.hpp"
#pragma once


class Particula :
	public RenderItem
{
private:
	//fuerza de rozamiento
	float damping;

	//masa inversa
	float inverse_mass;

	//struct medidas del shape
	struct Medidas { 
		float x_;

		union{
			float y_; //si no se necesitan no ocupan memoria
			float z_;
		};

		//constructores
		Medidas(int x) : x_(x) {};
		Medidas(int x, int y) : x_(x), y_(y) {};
		Medidas(int x, int y, int z) : x_(x), y_(y), z_(z) {};
	};
	
public:
	//enum tipos de shapes
	enum Shape { Capsule, Sphere, Box }; 

	//Posicion en el mundo
	Vector3 p; //tiene el transform...
	//Velocidad (lineal) en el mundo
	Vector3 v;
	//Aceleracion (lineal) en el mundo
	Vector3 a;

	physx::PxTransform newPos;

	//BOX --> ALTURA ANCHURA PROFUNDIDAD/ CAPSULE --> RADIO MAYOR RADIO MENOR/ SPHERE --> RADIO
	Particula(Shape shp, Medidas size, const physx::PxTransform* _trans, Vector3 _color, float inverse_mass = 1.0) : RenderItem(createShape(shp, size), _trans, _color),
		p(_trans->p), v(0, 0, 0), a(0, 0, 0), newPos(*_trans), inverse_mass(inverse_mass), damping(0.95) {};

	Particula(Shape shp, Medidas size, Vector3 _color, float inverse_mass = 1.0) : RenderItem(createShape(shp, size), _color), p(0, 0, 0), v(0, 0, 0), 
		a(0, 0, 0), inverse_mass(inverse_mass), damping(0.95) {};

	Particula() : RenderItem() {};

	void update(float time) { integrate(time); setTransform(); };

	//setDamping
	inline void setDamping(const float newDamping) { if (newDamping >= 0 && newDamping <= 1) damping = newDamping; } //else ---> avisar, lanzar una excepcion...?
	//Integracion
	void integrate(float t);
	//set inerse_mass
	inline void setInverseMass(const float newMass) { inverse_mass = newMass; };

protected:
	//crea la shape dependiendo del tipo y las medidas introducidas
	physx::PxShape* createShape(Shape tipo, Medidas size);
	//iguala el elemento p del Px auxiliar e iguala el transform de la particula a dicho Px
	inline void setTransform() { newPos.p = p; transform = &newPos; };

};

