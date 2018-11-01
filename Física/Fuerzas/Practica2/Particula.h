#pragma once
#include "RenderUtils.hpp"

class ParticleForceRegistry;

class Particula
{
private:
	
	RenderItem* renderItem = nullptr;                  //Render Item

	float damping;                                     //fuerza de rozamiento

	float inverse_mass;                                //masa inversa

	bool active = true;                                //active	

	float lifeTime_;                                   //lifetime

	physx::PxTransform transform;                      //transform

	Vector3 p;                                        //Posicion en el mundo

	Vector3 v;                                        //Velocidad (lineal) en el mundo

	Vector3 a;                                        //Aceleracion (lineal) en el mundo

	Vector3 force;                                    // Accumulated force	

	void integrate(float t);                         //Integracion

	void clearForce();                               // Clears accumulated force


public:

	static ParticleForceRegistry registry_;                     //variable estatica del registro de particulas --> todos tienen acceso al mismo

	
	enum Shape { Capsule, Sphere, Box };                       //enum tipos de shapes

	
	struct Medidas {                                          //struct medidas del shape
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


	Particula(RenderItem* rItem, float inverse_mass = 1.0) : renderItem(rItem), inverse_mass(inverse_mass), 
		damping(0.95), v(0, 0, 0), a(0, 0, 0), p(0, 0, 0), transform(p), lifeTime_(0), force(0, 0, 0) { renderItem->transform = &transform; };

	Particula() : renderItem(nullptr), inverse_mass(1), damping(0.95), lifeTime_(0) {};

	virtual ~Particula() { if (renderItem != nullptr) delete renderItem; };

	virtual void update(float time) { integrate(time); lifeTime_ += time; };

	//-------------------------------------------------------------------GETTERS------------------------------------------------------------

	//get invmass
	inline int getMass() const { return inverse_mass; };

	//get dumping
	inline float getDamping() const { return damping; };

	//getPosition
	inline Vector3 getPosition() const { return p; }

	//getAcceleration
	inline Vector3 getAcceleration() const { return a; }

	//getVelocity
	inline Vector3 getVelocity() const { return v; }

	//distancia recorrida desde el inicio
	inline const unsigned int getDistanceTraveled() { return p.magnitude(); };

	//isactive
	inline const bool isActive() { return active; };

	//tiempo de vida
	inline const float getLifeTime() { return lifeTime_; };

	//-------------------------------------------------------------------SETTERS--------------------------------------------------------------

	//setPosition
	inline void setPosition(const Vector3 pos) { p = pos; transform.p = p; };

	//setAcc
	inline void setAcceleration(const Vector3 a_) { a = a_; };

	//setVelocity
	inline void setVelocity(const Vector3 v_) { v = v_; };

	//set renderItem
	inline void setRenderItem(RenderItem* rn) { renderItem = rn; };

	//setDamping
	inline void setDamping(const float newDamping) { if (newDamping >= 0 && newDamping <= 1) damping = newDamping; } //else ---> avisar, lanzar una excepcion...?

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
	inline void setColor(Vector4 color_) { renderItem->color = color_; };

	//setActive and RegisterRenderItem
	inline void setActive() { active = true;  RegisterRenderItem(renderItem); };

	//setInactive and DeregisterRenderItem
	inline void setInactive() { active = false;  resetLifeTime();  DeregisterRenderItem(renderItem); };

	//set JUST THE BOOL ACTIVE 
	inline void setActive(bool nAct) { active = nAct; };

	//------------------------------------------------------------------------------OTHERS-------------------------------------------------

	// Add force to apply in next integration only
	void addForce(const Vector3& f);

	//reset tiempo de vida
	inline void resetLifeTime() { lifeTime_ = 0; };

protected:
	//crea la shape dependiendo del tipo y las medidas introducidas
	physx::PxShape* createShape(Shape tipo, Medidas size);
};

