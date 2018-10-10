#include "RenderUtils.hpp"
#pragma once


class Particula
{
private:
	//Render Item
	RenderItem* renderItem = nullptr;
	//fuerza de rozamiento
	float damping;

	//masa inversa
	float inverse_mass;

	//active
	bool active = true;

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
	Particula(RenderItem* rItem, float inverse_mass = 1.0) : renderItem(rItem), inverse_mass(inverse_mass), damping(0.95), v(0, 0, 0), a(0, 0, 0), p(0, 0, 0), newPos(0, 0, 0){};

	Particula() : renderItem(nullptr), inverse_mass(1), damping(0.95) {};

	virtual ~Particula() { if (renderItem != nullptr) delete renderItem; };

	void update(float time) { integrate(time); setTransform(); };

	//set renderItem
	inline void setRenderItem(RenderItem* rn) { renderItem = rn; };
	//setDamping
	inline void setDamping(const float newDamping) { if (newDamping >= 0 && newDamping <= 1) damping = newDamping; } //else ---> avisar, lanzar una excepcion...?
	//Integracion
	void integrate(float t);
	//set inerse_mass
	inline void setInverseMass(const float newMass) { inverse_mass = newMass; };
	//set shape
	inline void setShape(Shape shp, Medidas size) { renderItem->shape = createShape(shp, size); };
	//set color
	inline void setColor(Vector3 color_) { renderItem->color = color_; };
	//set transform
	inline void setTransform(const physx::PxTransform* trans) { renderItem->transform = trans; p = trans->p; newPos = *trans; };
	//isactive
	inline const bool isActive() { return active; };
	//setActive and RegisterRenderItem
	inline void setActive() { active = true;  RegisterRenderItem(renderItem); };
	//setInactive and DeregisterRenderItem
	inline void setInactive() { active = false;  DeregisterRenderItem(renderItem); };
	//set JUST THE BOOL ACTIVE 
	inline void setActive(bool nAct) { active = nAct; };
	//distancia recorrida desde el inicio
	inline const unsigned int getDistanceTraveled() { return p.magnitude(); };

protected:
	//crea la shape dependiendo del tipo y las medidas introducidas
	physx::PxShape* createShape(Shape tipo, Medidas size);
	//iguala el elemento p del Px auxiliar e iguala el transform de la particula a dicho Px
	inline void setTransform() { newPos.p = p; renderItem->transform = &newPos; };
};

