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

	//BOX --> ALTURA ANCHURA PROFUNDIDAD/ CAPSULE --> RADIO MAYOR RADIO MENOR/ SPHERE --> RADIO
	Particula(Shape shp, Medidas size, const physx::PxTransform* _trans, Vector3 _color) : RenderItem(createShape(shp, size), _trans, _color), 
		p(_trans->p.x, _trans->p.y, _trans->p.z) { };

	Particula(Shape shp, Medidas size, Vector3 _color) : RenderItem(createShape(shp, size), _color) { };

	Particula() : RenderItem() {};

	void update(float time) {}; //update para uso posterior

	void changeDamping(const float newDamping);
	//Integracion
	void integrate(float t);
	//cambiar masa
	void changeInverseMass(const float newMass);

protected:
	//crea la shape dependiendo del tipo y las medidas introducidas
	physx::PxShape* createShape(Shape tipo, Medidas size); 

};

