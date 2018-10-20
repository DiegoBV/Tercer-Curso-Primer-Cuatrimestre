#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"

#include "Particula.h"

#include "TemplatePool.h"

#include "Time_Generator.h"


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

std::vector<Particula*> particles; //vector para manejar las particulas

TemplatePool<Particula> pool; //pool de particulas creadas para disparar, por defecto se crean 30 al principio y se van reusando

Time_Generator g(Particula::Sphere, 0.01);

//------------------------------------------------ Constantes del disparo ---------------------------------------------------
const Particula::Shape DEF_SHAPE = Particula::Sphere;
const unsigned int DEF_SIZE = { 10 };
const Vector3 DEF_COLOR = {100, 0, 100};
const unsigned int DEF_VEL = 100;
const unsigned int DEF_ACC = 30;
const unsigned int DEF_DIST_TRAV = 2000;
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
	// ...
}

bool checkBullet(vector<Particula*>::iterator& it) {

	if ((*it)->getDistanceTraveled() > DEF_DIST_TRAV) {
		(*it)->setInactive();
		it = particles.erase(it);
		return true;
	}

	return false;
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	for (vector<Particula*>::iterator it = particles.begin(); it != particles.end();) {

		(*it)->update(t);
		if (!checkBullet(it)) { it++; } //si ninguna bala ha desaparecido se aumenta el iterador, si desaparece el iterador aumenta al borrar el contenido
	}

	g.update(t);
	// Add custom application code
	// ...
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Add custom application code
	// ...

	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

}

void shoot() {

	Particula* p = pool.getObject(); //se busca una particula inactiva en la pool (y se activa). Si no existe, se crea una nueva

	p->setShape(DEF_SHAPE, DEF_SIZE); //set de la forma, color, velocidad, aceleracion...

	p->setTransform(&PxTransform(GetCamera()->getEye()));
	p->setColor(DEF_COLOR);

	p->v = GetCamera()->getDir() * DEF_VEL; //sets de velocidad y aceleracion
	p->a = GetCamera()->getDir() * DEF_ACC;
	p->a.y = -100;

	particles.push_back(p); //se añade al vector de particulas para poder actualizarlas
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	switch(toupper(key))
	{
	case 'B':
		break;
	case ' ':
		break;
	case 'X': 
	{
		shoot();
		break;
	}
	default:
		break;
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
