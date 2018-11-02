#pragma once
#include "ParticleForceGenerator.h"
class Wind :
	public ParticleForceGenerator
{
private:
	float wind_force_;

	Vector3 wind_direction_;

	Vector3 center;               //sphere center

	physx::PxTransform transform;

	float rad;                   //sphere radius

	RenderItem* rn = nullptr;

	bool is_inside(Particle* particle);

public:
	Wind() : wind_force_(0), wind_direction_(0) {};

	virtual ~Wind() { delete rn; };

	Wind(float wind_force, Vector3 wind_direction, Vector3 center = { 0, 0, 0 }, float rad = 50) : 
		wind_force_(wind_force), wind_direction_(wind_direction), center(center), rad(rad), transform(center), rn(new RenderItem()){ 
			rn->shape = CreateShape(physx::PxSphereGeometry(rad)); rn->transform = &transform; rn->color = { 0, 0, 1, 0 }; RegisterRenderItem(rn); wind_direction_.normalize(); };

	inline float getWindForce() const { return wind_force_; };

	inline Vector3 getWindDirection() const { return wind_direction_; };

	inline void setWindForce(float wf) { wind_force_ = wf; };

	inline void setWindDirection(Vector3 wd) { wd.normalize(); wind_direction_ = wd; };

	virtual void updateForce(Particle* particle, float t);

	inline void changeDirection() { std::swap(wind_direction_.x, wind_direction_.y); std::swap(wind_direction_.y, wind_direction_.z); };

	virtual void handle_event(unsigned char key);
};

