#include "SpringManager.h"

void SpringManager::addParticle_to_AnchoredSpring(Vector3 * anchor, float k, float rest_length)
{
	particles.push_back(new Particle(new RenderItem()));                                        //creacion de la particula
	particles.back()->setCapsuleShape(1, 2);
	particles.back()->setActive();
	particles.back()->setDamping(0.8);

	ParticleAnchoredSpring* aSpring = new ParticleAnchoredSpring(anchor, k, rest_length);      //creacion del muelle
	springs.push_back(aSpring);

	Particle::registry_.add(particles.back(), aSpring);
	Particle::registry_.add(particles.back(), aSpring->getWind());

	register_particle_in_generators(particles.back());
}

void SpringManager::addRigid_Body_to_AnchoredSpring(physx::PxRigidDynamic* obj, Vector3 * anchor, float k, float rest_length)
{
	ParticleAnchoredSpring* aSpring = new ParticleAnchoredSpring(anchor, k, rest_length);      //creacion del muelle
	springs.push_back(aSpring);

	Particle::registry_.add(obj, aSpring);
	Particle::registry_.add(obj, aSpring->getWind());

	//lo agrega sin mas, sin agregarle mas generadores que los que ya tenga propios ---> importante
}

void SpringManager::addSpring_of_TwoParticles(float k, float rest_length, Vector3 posONE, Vector3 posOTHER, Particle* one, Particle * other)
{
	if (one == nullptr) {                                                //set de la primera particula
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
		particles.back()->setPosition(posONE);
		particles.back()->setColor({ 1, 0, 0, 1 });
		particles.back()->setDamping(0.8);
	}
	else {
		particles.push_back(one); //se va a borrar... si da fallos es esto
	}
	one = particles.back();

	if (other == nullptr) {                                                  //set de la segunda particula
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
		particles.back()->setPosition(posOTHER);
		particles.back()->setColor({ 0, 1, 0, 1 });
		particles.back()->setDamping(0.8);
	}
	else {
		particles.push_back(other); //se va a borrar... si da fallos es esto
	}
	other = particles.back();


	ParticleSpring* springONE = new ParticleSpring(other, k, rest_length);          //primer muelle
	springs.push_back(springONE);

	Particle::registry_.add(one, springONE);
	Particle::registry_.add(one, springONE->getWind());

	ParticleSpring* springOTHER = new ParticleSpring(one, k, rest_length);       //segundo muelle
	springs.push_back(springOTHER);

	Particle::registry_.add(other, springOTHER);
	//Particle::registry_.add(other, springOTHER->getWind());

	register_particle_in_generators(one);
	register_particle_in_generators(other);
}

void SpringManager::addSpring_of_TwoRigidBodies(float k, float rest_length, physx::PxRigidDynamic * one, physx::PxRigidDynamic * other)
{
	ParticleSpring* springONE = new ParticleSpring(other, k, rest_length);          //primer muelle
	springs.push_back(springONE);

	Particle::registry_.add(one, springONE);
	Particle::registry_.add(one, springONE->getWind());

	ParticleSpring* springOTHER = new ParticleSpring(one, k, rest_length);       //segundo muelle
	springs.push_back(springOTHER);

	Particle::registry_.add(other, springOTHER);

	one->addTorque({ 0, 90, 0 });
}

void SpringManager::addParticle_to_Liquid(Vector3 pos, float _maxDepth, float _volume, float _waterHeight, float _liquidDensity)
{
	particles.push_back(new Particle(new RenderItem()));                  //set de la particula
	particles.back()->setCapsuleShape(1, 2);
	particles.back()->setActive();
	particles.back()->setPosition(pos);
	particles.back()->setDamping(.8);

	ParticleBuoyancy* b = new ParticleBuoyancy(_maxDepth, _volume, _waterHeight, _liquidDensity);     //creacion del generador de flotacion
	springs.push_back(b);

	Particle::registry_.add(particles.back(), b);
	Particle::registry_.add(particles.back(), b->getWind());

	register_particle_in_generators(particles.back());

	particles.push_back(new Particle(new RenderItem(), 0));       //"agua"
	particles.back()->setBoxShape(100, .1, 100);
	particles.back()->setActive();
	particles.back()->setPosition(pos);
	particles.back()->setColor({0, 0, 1, 1});
}

void SpringManager::addRigidBody_to_Liquid(physx::PxRigidDynamic* rb, float _maxDepth, float _volume, float _waterHeight, float _liquidDensity)
{
	ParticleBuoyancy* b = new ParticleBuoyancy(_maxDepth, _volume, _waterHeight, _liquidDensity);     //creacion del generador de flotacion
	springs.push_back(b);

	Particle::registry_.add(rb, b);
	Particle::registry_.add(rb, b->getWind());

	particles.push_back(new Particle(new RenderItem(), 0));       //"agua"
	particles.back()->setBoxShape(100, .1, 100);
	particles.back()->setActive();
	particles.back()->setPosition(rb->getGlobalPose().p);
	particles.back()->setColor({ 0, 0, 1, 1 });
}

void SpringManager::update(float t)
{
	for (Particle* p : particles) {
		p->update(t);
	}
}

void SpringManager::handle_event(unsigned char key)
{
	for (ParticleForceGenerator* gen : springs) {
		gen->handle_event(key);
	}
}
