#include "SpringManager.h"

void SpringManager::addParticle_to_AnchoredSpring(Vector3 * anchor, float k, float rest_length)
{
	particles.push_back(new Particle(new RenderItem()));
	particles.back()->setCapsuleShape(1, 2);
	particles.back()->setActive();

	ParticleAnchoredSpring* aSpring = new ParticleAnchoredSpring(anchor, k, rest_length);
	springs.push_back(aSpring);

	addGenerator(aSpring->getWind());

	Particle::registry_.add(particles.back(), aSpring);

	register_particle_in_generators(particles.back());
}

void SpringManager::addSpring_of_TwoParticles(float k, float rest_length, Particle* one, Particle * other)
{
	if (one == nullptr) {
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
	}
	else {
		particles.push_back(one); //se va a borrar... si da fallos es esto
	}
	one = particles.back();

	if (other == nullptr) {
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
	}
	else {
		particles.push_back(other); //se va a borrar... si da fallos es esto
	}
	other = particles.back();

	//ParticleSpring* spring = new ParticleSpring(...);
	//springs.push_back(spring);

	//addGenerator(spring->getWind());

	//Particle::registry_.add(one, spring);
	//Particle::registry_.add(other), spring);

	register_particle_in_generators(one);
	register_particle_in_generators(other);
}

void SpringManager::update(double t)
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
