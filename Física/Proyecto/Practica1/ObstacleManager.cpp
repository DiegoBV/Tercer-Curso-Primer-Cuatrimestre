#include "ObstacleManager.h"



void ObstacleManager::generateObstacle()
{
	RenderItem* rn = nullptr;
	obstaculos.push({ generateStaticElement(rn, { 0, 0, 0 }, shape_, {10, 10, 10}), rn }); //puedo especificarle tamanyo y eso
}

void ObstacleManager::reparteObstaculos()
{
	float z = -dis_between_obs*10;
	for (size_t i = 0; i < MAX_OBS; i++){
		Obstacle obj = obstaculos.front();
		obstaculos.pop();
		Vector3 pos = generateRandomPos({ 0, 0, 4000 }, dis_between_obs, FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2);
		obj.obstacle->setGlobalPose({ pos.x, 20, z });
		z -= dis_between_obs;

		obstaculos.push(obj);
	}
}

void ObstacleManager::checkFloor()
{
	//chequea si el personaje ha sobrepasado la mitad del suelo, y mueve el suelo
	if (checkDistanceBtwChar(floor->getGlobalPose().p.z - FLOOR_SIZE.z_ / 2)) {
		floor->setGlobalPose({ floor->getGlobalPose().p.x , floor->getGlobalPose().p.y, floor->getGlobalPose().p.z - FLOOR_SIZE.z_ });
	}
}

void ObstacleManager::checkObstacle()
{
	//chuequea si el primer obstaculo de la cola (segun la estructura es el mas cercano al personaje) y lo mueve. Podria
	// mover esto a alguna clase de arriba que reciba al personaje, porq muchas cosas hay que moverlas... (igual tengo q hacer una clase abstacta que herede de 
	//manager que solo tenga posicion y character... Por ejemplo, las fuentes o los springs se tienen que mover...)
	Obstacle obj = obstaculos.front();

	if (checkDistanceBtwChar(obj.obstacle->getGlobalPose().p.z - dis_between_obs)) {
		Vector3 newPos = generateRandomPos(obj.obstacle->getGlobalPose().p, dis_between_obs * (MAX_OBS + 2), FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2);
		if (obj.type == 1) {
			obj.obstacle->setGlobalPose({obj.obstacle->getGlobalPose().p.x, newPos.y, newPos.z });
			sp.suelo->setGlobalPose({ sp.suelo->getGlobalPose().p.x,sp.suelo->getGlobalPose().p.y, newPos.z + ELASTIC_BED_SIZE.z_/2 });
			sp.rn_suelo->color = generateRandomColor();
		}
		else if (obj.type == 2) {
			obj.obstacle->setGlobalPose({ obj.obstacle->getGlobalPose().p.x, 11, newPos.z });
			do_.capsula->setGlobalPose({ obj.obstacle->getGlobalPose().p.x, 55, newPos.z});
			do_.capsula->clearForce();
			do_.capsula->clearTorque();
			do_.capsula->setLinearVelocity({ 0, 0, 0 });
			do_.capsula->setAngularVelocity({ 0, 0, 0 });
			do_.rn_->color = generateRandomColor();
		}
		else if (obj.type == 3) {
			obj.obstacle->setGlobalPose({ obj.obstacle->getGlobalPose().p.x, newPos.y, newPos.z });
			ww.w->setCenter({ obj.obstacle->getGlobalPose().p.x, newPos.y, newPos.z + 200 });
		}
		else {
			obj.obstacle->setGlobalPose({ newPos.x, newPos.y, newPos.z }); //esto hay q cambiarlo a una posicion random por delante
		}
		obj.rn->color = generateRandomColor();
		obstaculos.pop();
		obstaculos.push(obj);
	}
}

void ObstacleManager::checkElasticBed()
{
	if (checkDistanceBtwChar(sp.suelo->getGlobalPose().p.z + ELASTIC_BED_SIZE.z_)) {
 		ch->setNewJumpForce(IN_JUMP_FORCE * 2);
	}
	else {
		ch->setNewJumpForce(IN_JUMP_FORCE);
	}
}

void ObstacleManager::checkFeedback()
{
	if (feedback->getPos().z != ww.w->getCenter().z) {
		feedback->setPos({ feedback->getPos().x, feedback->getPos().y, ww.w->getCenter().z });
	}
}

void ObstacleManager::generateSpecialObstacle()
{
	RenderItem* rn = nullptr;
	RenderItem* rn_suelo = nullptr;
	sp = SpecialObstacle(generateStaticElement(rn, { 0, 0, -1300 }, shape_, { 50, 70, 1 }), 
		generateStaticElement(rn_suelo, { 0, 14.13, -1300 + ELASTIC_BED_SIZE.z_ }, shape_, ELASTIC_BED_SIZE), rn, rn_suelo);
	obstaculos.push(sp);
}

void ObstacleManager::generateDynamicObstacle()
{
	RenderItem* rn = nullptr;
	RenderItem* rn_other = nullptr;
	physx::PxRigidStatic* other = generateStaticElement(rn_other, { 0, 11, -2600 }, shape_, { 50, .1, 50 });
	physx::PxRigidDynamic* one = generateDynamicElement(rn, { 0, 55, -2600 }, Particle::Capsule, { 20, 20 });
	do_ = DynamicObstacle(one, rn, other, rn_other);
	obstaculos.push(do_);
	register_rigid_body_in_generators(do_.capsula);
}

void ObstacleManager::generateWindWall()
{
	RenderItem* rn = nullptr;
	physx::PxRigidStatic* one = generateStaticElement(rn, { 0, 0, -4000 }, shape_, { 50, 70, 1 });
	Wind* w = new Wind(220, { 0, 1, 0 }, { 0, 0, -3800 }, 100);

	ww = WindWall(w, one, rn);

	obstaculos.push(ww);
}

void ObstacleManager::generateFloor()
{
	//genera el suelo....
	RenderItem* rn = nullptr;
	floor = generateStaticElement(rn, { 0, 15, 0 }, Particle::Box, FLOOR_SIZE, {1, 1, 1, 1});
}

ObstacleManager::ObstacleManager(): IN_JUMP_FORCE(0)
{
}


ObstacleManager::~ObstacleManager()
{
	if (ww.w != nullptr) {
		delete ww.w;
		ww.w = nullptr;
	}
}

void ObstacleManager::update(float t)
{
	checkFloor();
	checkObstacle();
	checkElasticBed();
	checkFeedback();
}
