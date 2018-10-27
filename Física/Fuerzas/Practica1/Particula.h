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

	//lifetime
	double lifeTime_;

	// Accumulated force
	Vector3 force;

	// Clears accumulated force
	void clearForce();

	// Add force to apply in next integration only
	void addForce(const Vector3& f);

	//transform
	physx::PxTransform transform;
	
public:
	//enum tipos de shapes
	enum Shape { Capsule, Sphere, Box };

	//struct medidas del shape
	struct Medidas { 
		float x_;

		union{
			float y_; //si no se necesitan no ocupan memoria
			float z_;
		};

		//constructores
		Medidas(float x) : x_(x) {};
		Medidas(float x, float y) : x_(x), y_(y) {};
		Medidas(float x, float y, float z) : x_(x), y_(y), z_(z) {};
	};

	//Posicion en el mundo
	Vector3 p; //tiene el transform...
	//Velocidad (lineal) en el mundo
	Vector3 v;
	//Aceleracion (lineal) en el mundo
	Vector3 a;

	Particula(RenderItem* rItem, float inverse_mass = 1.0) : renderItem(rItem), inverse_mass(inverse_mass), damping(0.95), v(0, 0, 0), a(0, 0, 0), p(0, 0, 0), transform(p), lifeTime_(0) { renderItem->transform = &transform; };

	Particula() : renderItem(nullptr), inverse_mass(1), damping(0.95), lifeTime_(0) {};

	virtual ~Particula() { if (renderItem != nullptr) delete renderItem; };

	virtual void update(double time) { integrate(time); lifeTime_ += time; };

	//set renderItem
	inline void setRenderItem(RenderItem* rn) { renderItem = rn; };
	//setDamping
	inline void setDamping(const float newDamping) { if (newDamping >= 0 && newDamping <= 1) damping = newDamping; } //else ---> avisar, lanzar una excepcion...?
	//Integracion
	void integrate(float t);
	//set inerse_mass
	inline void setMass(const float newMass) { inverse_mass = newMass; };
	//set shape si no tiene forma
	inline void setShape(Shape shp, Medidas size) { renderItem->shape = createShape(shp, size);};
	//setSphereShape
	inline void setSphereShape(float r) { renderItem->shape = createShape(Sphere, r); };
	//setCapsuleShape
	inline void setCapsuleShape(float r, float R) { renderItem->shape = createShape(Capsule, { r, R }); };
	//setBoxShape
	inline void setBoxShape(float x, float y, float z) { renderItem->shape = createShape(Box, { x, y, z }); };
	//set color
	inline void setColor(Vector3 color_) { renderItem->color = color_; };
	//set transform
	inline void setPosition(const Vector3 pos) { p = pos; transform.p = p; };
	//getTransform
	inline Vector3 getPosition() const { return p; }
	//isactive
	inline const bool isActive() { return active; };
	//setActive and RegisterRenderItem
	inline void setActive() { active = true;  RegisterRenderItem(renderItem); };
	//setInactive and DeregisterRenderItem
	inline void setInactive() { active = false;  resetLifeTime();  DeregisterRenderItem(renderItem); };
	//set JUST THE BOOL ACTIVE 
	inline void setActive(bool nAct) { active = nAct; };
	//distancia recorrida desde el inicio
	inline const unsigned int getDistanceTraveled() { return p.magnitude(); };
	//tiempo de vida
	inline const float lifeTime() { return lifeTime_; };
	//reset tiempo de vida
	inline void resetLifeTime() { lifeTime_ = 0; };

protected:
	//crea la shape dependiendo del tipo y las medidas introducidas
	physx::PxShape* createShape(Shape tipo, Medidas size);
};

