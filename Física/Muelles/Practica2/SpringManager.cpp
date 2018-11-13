#include "SpringManager.h"

void SpringManager::addParticle_to_AnchoredSpring(Vector3 * anchor, float k, float rest_length)
{
	particles.push_back(new Particle(new RenderItem()));
	particles.back()->setCapsuleShape(1, 2);
	particles.back()->setActive();

	ParticleAnchoredSpring* aSpring = new ParticleAnchoredSpring(anchor, k, rest_length);
	springs.push_back(aSpring);

	Particle::registry_.add(particles.back(), aSpring);
	Particle::registry_.add(particles.back(), aSpring->getWind());

	register_particle_in_generators(particles.back());
}

void SpringManager::addSpring_of_TwoParticles(float k, float rest_length, Vector3 posONE, Vector3 posOTHER, Particle* one, Particle * other)
{
	if (one == nullptr) {
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
		particles.back()->setPosition(posONE);
		particles.back()->setColor({ 1, 0, 0, 1 });
	}
	else {
		particles.push_back(one); //se va a borrar... si da fallos es esto
	}
	one = particles.back();

	if (other == nullptr) {
		particles.push_back(new Particle(new RenderItem()));
		particles.back()->setCapsuleShape(1, 2);
		particles.back()->setActive();
		particles.back()->setPosition(posOTHER);
		particles.back()->setColor({ 0, 1, 0, 1 });
	}
	else {
		particles.push_back(other); //se va a borrar... si da fallos es esto
	}
	other = particles.back();


	ParticleSpring* springONE = new ParticleSpring(other, k, rest_length);
	springs.push_back(springONE);

	Particle::registry_.add(one, springONE);
	Particle::registry_.add(one, springONE->getWind());

	ParticleSpring* springOTHER = new ParticleSpring(one, k, rest_length);
	springs.push_back(springOTHER);

	Particle::registry_.add(other, springOTHER);
	Particle::registry_.add(other, springOTHER->getWind());

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
