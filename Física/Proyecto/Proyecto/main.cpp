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

#include "callbacks.hpp"

#include "Wind.h"

#include "Shot_Manager.h"

#include "GrenadeManager.h"

#include "ParticleAnchoredSpring.h"

#include "SpringManager.h"

#include "CharacterManager.h"

#include "RigidSystem_Manager.h"

#include "ObstacleManager.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;

TemplatePool<Particle> pool;                                      //pool de Particles creadas para disparar, por defecto se crean 300 al principio y se van reusando

vector<Manager*> managers;                                         // vector de managers (clase abstracta) para manejar mejor sus handle y updates

vector<ParticleForceGenerator*> generators;                        // vector de generators para no tener muchas variables globales

vector<Wind*> vientos;                                            //manejador de vientos

Vector3 centerAnchoredSpring(0, 10, 0);

MainCharacter* pj;

CharacterManager* chr_man;

PxRigidStatic* floor_;

ContactReportCallback gContactReportCallback;

void menu(ObstacleManager* man);

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	sceneDesc.gravity = { 0, -100, 0 };
	gScene = gPhysics->createScene(sceneDesc);
	// ------------------------------------------------------

	// Add custom application code
	//----------------------------------------------------GENERATORS-------------------------------------------------------

	ParticleGravity* grav_gen_ = new ParticleGravity({ 0, -80, 0 });
	generators.push_back(grav_gen_);

	ParticleGravity* grav_gen_2_ = new ParticleGravity({ 0, -10, 0 });
	generators.push_back(grav_gen_2_);

	ParticleGravity* ingrav_gen_ = new ParticleGravity({ 0, 2, 0 });
	generators.push_back(ingrav_gen_);

	ParticleDrag* drag_gen = new ParticleDrag(1, 1);
	generators.push_back(drag_gen);

	Wind* wind = new Wind(100, { 1, 0, 0 }, { 0, 30, 0 });
	generators.push_back(wind);
	vientos.push_back(wind);

	Wind* wind2 = new Wind(200, { 0, 0, 1 }, { 100, 40, 0 });
	generators.push_back(wind2);
	vientos.push_back(wind2);

	ParticleGravity* grav_diana = new ParticleGravity({ 0.001, -0.001, 0.001 });
	generators.push_back(grav_diana);

	//----------------------------------------------------MANAGERS-------------------------------------------------------

	//MainCharacter
	chr_man = new CharacterManager(250, gPhysics, gScene, {6, 20, 0});
	//chr_man->addGenerator(drag_gen);
	chr_man->addGenerator(wind);
	chr_man->addGenerator(wind2);
	managers.push_back(chr_man);
	chr_man->initCharacter();
	pj = chr_man->getCharacter();

	GrenadeManager* gren_man = new GrenadeManager(pj);
	gren_man->addGenerator(grav_gen_);
	generators.push_back(gren_man->getBlast());
	managers.push_back(gren_man);

	FireworkManager* fManager_ = new FireworkManager(pj);
	fManager_->addGenerator(grav_gen_);
	fManager_->switch_activate();
	managers.push_back(fManager_);

	Time_GeneratorManager* t_gen = new Time_GeneratorManager(Particle::Sphere, 0.01, &pool, pj, {25, 50, 0});
	t_gen->addGenerator(grav_gen_);
	t_gen->addGenerator(gren_man->getBlast());
	t_gen->addGenerator(wind);
	t_gen->addGenerator(wind2);
	managers.push_back(t_gen);

	Time_GeneratorManager* t_gen2 = new Time_GeneratorManager(Particle::Sphere, 0.01, &pool, pj, { 0, 20, -3800 });
	t_gen2->addGenerator(grav_gen_);
	t_gen2->addGenerator(gren_man->getBlast());
	t_gen2->addGenerator(wind);
	t_gen2->addGenerator(wind2);
	managers.push_back(t_gen2);

	SpringManager* sp_man = new SpringManager(pj);
	sp_man->addGenerator(grav_gen_2_);
	//sp_man->addGenerator(drag_gen);
	//sp_man->addParticle_to_AnchoredSpring(&centerAnchoredSpring, 1, 10);
	sp_man->addSpring_of_TwoParticles(2, 3.5, { 100, 90, -80 }, {10, 30, -80});
	sp_man->addSpring_of_TwoParticles(10, 1, { -100, 110, -110 }, { -100, 150, -1100 });
	sp_man->addParticle_to_Liquid({ -80, 15, -100 }, 3, 4, 20, {0.75, 0.1, 0.2, 1}, 10);
	sp_man->addParticle_to_Liquid({ 80, 15, -150 }, 3, 4, 20, { 0.75, 0.5, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ 81, 15, -450 }, 4, 4, 17, { 0.15, 0.1, 0.92, 1 }, 10);
	sp_man->addParticle_to_Liquid({ -81, 15, -300 }, 7, 4, 18, { 0.25, 0.81, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ 81, 15, -200 }, 3, 4, 15, { 0.15, 0.1, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ 151, 15, -200 }, 3, 4, 15, { 0.15, 0.1, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ -91, 15, -200 }, 3, 4, 15, { 0.15, 0.1, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ 91, 15, -200 }, 1, 3, 22, { 0.15, 0.1, 0.2, 1 }, 10);
	sp_man->addParticle_to_Liquid({ -151, 15, -200 }, 2, 3, 18, { 0.15, 0.1, 0.2, 1 }, 10);
	//sp_man->addRigidBody_to_Liquid(pj->getPj(), 30, 40, 20, 100);
	managers.push_back(sp_man);

	
	/*Shot_Manager* s_man = new Shot_Manager(&pool);
	s_man->addGenerator(ingrav_gen_);
	s_man->addGenerator(wind);
	s_man->addGenerator(wind2);
	s_man->addGenerator(gren_man->getBlast());
	managers.push_back(s_man);


	//para probar las granadas
	Time_GeneratorManager* diana = new Time_GeneratorManager(Particle::Sphere, 0.1, &pool, 2, 1, 10, { 300, 0, 0 });
	diana->addGenerator(grav_diana);
	diana->addGenerator(gren_man->getBlast());
	managers.push_back(diana);*/


	//RigidBody
	RigidSystem_Manager* rs_man = new RigidSystem_Manager(Particle::Box, .1, gPhysics, gScene, pj);
	rs_man->addGenerator(gren_man->getBlast());
	rs_man->setOn(false);
	//rs_man->addGenerator(wind);
	//rs_man->addGenerator(wind2);
	//rs_man->generateStaticElement({ 0, 15, 0 }, Particle::Box, { 50, .1, 1000 });
	//sp_man->addRigid_Body_to_AnchoredSpring(rs_man->generateDynamicElement(), &centerAnchoredSpring, 1, 10);
	//sp_man->addSpring_of_TwoRigidBodies(1, 5, rs_man->generateDynamicElement({10, 0, 0}, Particle::Sphere), rs_man->generateDynamicElement());
	//sp_man->addRigidBody_to_Liquid(rs_man->generateDynamicElement({0, -10, 0}), 3, 4, 1, 30);
	managers.push_back(rs_man);
	

	//Manager de obstaculos
	ObstacleManager* obs_man = new ObstacleManager(chr_man->getCharacter(), Particle::Box, gPhysics, gScene, t_gen2);
	obs_man->addGenerator(gren_man->getBlast());
	obs_man->setDifficulty(ObstacleManager::Hard);
	obs_man->initObstacles();
	chr_man->addGenerator(obs_man->getWind());
	t_gen2->addGenerator(obs_man->getWind());
	managers.push_back(obs_man);
	floor_ = obs_man->getFloor();

	chr_man->register_rigid_body_in_generators(pj->getPj());
	// ...
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	if (actor1->getName() == pj->getPjName() || actor2->getName() == pj->getPjName()) {
		pj->setCanJump(true);
	}
}



// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	mciSendString("play Fondo.wav", NULL, 0, NULL);

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	Particle::registry_.updateForces(t);
	// Add custom application code
	if (!pj->isDead()) {
		for (Manager* man : managers) {
			man->update(t);
		}
		for (Wind* w : vientos) {
			if (pj->getPj()->getGlobalPose().p.z < w->getCenter().z - 100)
				w->setCenter({ w->getCenter().x, w->getCenter().y, w->getCenter().z - 2500 });
		}

		//onCollision(floor_, pj->getPj());
		GetCamera()->update(t);
	}
	else {
		chr_man->resCharacter(t);
		setPosZ(GetCamera()->getEye().z - 100);
		setText("KEEP TRYING, LOSER");
	}

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

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
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

	if (toupper(key) == 'P') {
		switchDebug();
	}

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

