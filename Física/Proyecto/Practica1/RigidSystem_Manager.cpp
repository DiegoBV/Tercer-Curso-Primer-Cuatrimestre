#include "RigidSystem_Manager.h"


void RigidSystem_Manager::generateNewElement(double t)
{
	tiempo_transcurrido += t;
	if (tiempo_transcurrido > next_period && total_ < MAX_ELEM_) {

		physx::PxTransform transform(pos);

		physx::PxRigidDynamic* obj = gPhysics->createRigidDynamic(transform);            //creo el rigid dinamico

		physx::PxShape* s = Particle::createShape(Particle::Shape(rand()% 3), { 1, 1, 1 });          //shape

		obj->attachShape(*s);

		physx::PxRigidBodyExt::updateMassAndInertia(*obj, 1);                          //update de la masa

		gScene->addActor(*obj);                                                       //lo anyado como actor

		rn_items.push_back(new RenderItem(s, obj, generateRandomColor()));           //creo el renderItem y lo pusheo para poder borrarlo facilmente

		next_period = tiempo_transcurrido + time_inter;                             //actualizo el tiempo

		register_rigid_body_in_generators(obj);                                   //register en todos los generadores asociados

		rigidos.push_back(obj);

		total_++;                                                                 //actualizo el total
	}
}

void RigidSystem_Manager::update(float t)
{
	if (isOn()) {
		if (checkDistanceBtwChar(pos.z - 100)) { pos.z = generateRandomPos(pos, 00, FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2).z; }
		generateNewElement(t);
	}
}

void RigidSystem_Manager::handle_event(unsigned char key)
{
	System_Manager::handle_event(key);

	switch (toupper(key))
	{
	case 'O':
		generateDynamicElement({ (float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100) });
		break;
	case 'P':
		generateStaticElement({ (float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100) });
		break;
	default:
		break;
	}
}

physx::PxRigidDynamic* RigidSystem_Manager::generateDynamicElement(Vector3 pos, Particle::Shape shp, Particle::Medidas size, physx::PxReal density)
{
	physx::PxTransform transform(pos);

	physx::PxRigidDynamic* obj = gPhysics->createRigidDynamic(transform);            //creo el rigid dinamico

	physx::PxShape* s = Particle::createShape(shp, size);          //shape

	obj->attachShape(*s);

	physx::PxRigidBodyExt::updateMassAndInertia(*obj, density);                          //update de la masa

	gScene->addActor(*obj);                                                       //lo anyado como actor

	rn_items.push_back(new RenderItem(s, obj, generateRandomColor()));           //creo el renderItem y lo pusheo para poder borrarlo facilmente

	register_rigid_body_in_generators(obj);                                   //register en todos los generadores asociados

	return obj;
}

physx::PxRigidStatic* RigidSystem_Manager::generateStaticElement(Vector3 pos, Particle::Shape shp, Particle::Medidas size, Vector4 c)
{
	physx::PxTransform transform(pos);

	physx::PxRigidStatic* obj = gPhysics->createRigidStatic(transform);           //creo el rigid dinamico

	physx::PxShape* s = Particle::createShape(shp, size);                        //shape

	obj->attachShape(*s);

	gScene->addActor(*obj);                                                       //lo anyado como actor

	rn_items.push_back(new RenderItem(s, obj, generateRandomColor()));           //creo el renderItem y lo pusheo para poder borrarlo facilmente
	if(c.w == -1)
		rn_items.back()->color = generateRandomColor();
	else {
		rn_items.back()->color = c;
	}

	return obj;
}

