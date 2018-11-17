#include "RigidSystem_Manager.h"


void RigidSystem_Manager::generateNewElement(double t)
{
	tiempo_transcurrido += t;
	if (tiempo_transcurrido > next_period && total_ < MAX_ELEM_) {
		physx::PxTransform transform(pos);

		physx::PxRigidDynamic* obj = gPhysics->createRigidDynamic(transform);
		physx::PxShape* s = Particle::createShape(Particle::Box, { 1, 1, 1 });
		obj->attachShape(*s); //maybe peta
		physx::PxRigidBodyExt::updateMassAndInertia(*obj, 1); //??
		gScene->addActor(*obj);
		rn_items.push_back(new RenderItem(s, obj, generateRandomColor()));
		next_period = tiempo_transcurrido + time_inter;
		total_++;
	}
}

void RigidSystem_Manager::update(double t)
{
	generateNewElement(t);
}
