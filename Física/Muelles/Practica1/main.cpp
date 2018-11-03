#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"

#include "Particle.h"

#include "TemplatePool.h"

#include "Time_GeneratorManager.h"

#include "FireworkManager.h"

#include "ParticleGravity.h"

#include "ParticleDrag.h"

#include "Wind.h"

#include "Shot_Manager.h"

#include "GrenadeManager.h"

#include "ParticleAnchoredSpring.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

TemplatePool<Particle> pool;                                      //pool de Particles creadas para disparar, por defecto se crean 300 al principio y se van reusando

vector<Manager*> managers;                                         // vector de managers (clase abstracta) para manejar mejor sus handle y updates

vector<ParticleForceGenerator*> generators;                        // vector de generators para no tener muchas variables globales

Particle* p = new Particle(new RenderItem());

//---------------------------------------------------------------------------------------------------------------------------

// Initialize physics engine
// Add custom code at the end of the function
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// Add custom application code
	//----------------------------------------------------GENERATORS-------------------------------------------------------

	ParticleGravity* grav_gen_ = new ParticleGravity({ 0, -1, 0 });
	generators.push_back(grav_gen_);
	ParticleGravity* ingrav_gen_ = new ParticleGravity({ 0, 2, 0 });
	generators.push_back(ingrav_gen_);;
	Wind* wind = new Wind(30, { 1, 0, 0 }, {0, -30, 0});
	generators.push_back(wind);
	Wind* wind2 = new Wind(30, { 0, 0, 1 }, { 100, -40, 0 });
	generators.push_back(wind2);
	ParticleGravity* grav_diana = new ParticleGravity({ 0.001, -0.001, 0.001 });
	generators.push_back(grav_diana);
	ParticleAnchoredSpring* spring = new ParticleAnchoredSpring(new Vector3(0, 10, 0), 10, 1); //es new por ahora, seria una referencia luego
	
	p->setCapsuleShape(1, 2);
	p->setActive();
	Particle::registry_.add(p, spring);
	//Particle::registry_.add(p, grav_gen_);
	//----------------------------------------------------MANAGERS-------------------------------------------------------

	GrenadeManager* gren_man = new GrenadeManager();
	gren_man->addGenerator(grav_gen_);
	generators.push_back(gren_man->getBlast());
	managers.push_back(gren_man);
	FireworkManager* fManager_ = new FireworkManager();
	fManager_->addGenerator(grav_gen_);
	managers.push_back(fManager_);
	Time_GeneratorManager* t_gen = new Time_GeneratorManager(Particle::Sphere, 0.0001, &pool);
	t_gen->addGenerator(grav_gen_);
	t_gen->addGenerator(gren_man->getBlast());
	t_gen->addGenerator(wind);
	t_gen->addGenerator(wind2);
	managers.push_back(t_gen);
	Shot_Manager* s_man = new Shot_Manager(&pool);
	s_man->addGenerator(ingrav_gen_);
	s_man->addGenerator(wind);
	s_man->addGenerator(wind2);
	s_man->addGenerator(gren_man->getBlast());
	managers.push_back(s_man);
	//para probar las granadas
	Time_GeneratorManager* diana = new Time_GeneratorManager(Particle::Sphere, 0.1, &pool, 2, 1, 10, {300, 0, 0});
	diana->addGenerator(grav_diana);
	diana->addGenerator(gren_man->getBlast());
	managers.push_back(diana);
	// ...
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	Particle::registry_.updateForces(t);
	// Add custom application code
	for (Manager* man : managers) {
		man->update(t);
	}
	p->update(t);
	// ...
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Add custom application code
	for (Manager* man : managers) {
		delete man;
		man = nullptr;
	}

	for (ParticleForceGenerator* gen : generators) {
		delete gen;
		gen = nullptr;
	}
	// ...

	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	for (Manager* man : managers) {
		man->handle_event(key);
	}
	for (ParticleForceGenerator* gen : generators) {
		gen->handle_event(key);
	}
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
