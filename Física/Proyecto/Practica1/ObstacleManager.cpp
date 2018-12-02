#include "ObstacleManager.h"



void ObstacleManager::generateObstacle()
{
	obstaculos.push({ generateStaticElement({ 0, 0, 0 }, shape_, {10, 10, 10}) }); //puedo especificarle tamanyo y eso
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
		Vector3 newPos = generateRandomPos(obj.obstacle->getGlobalPose().p, dis_between_obs * MAX_OBS, FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2);
		obj.obstacle->setGlobalPose({newPos.x, newPos.y, newPos.z}); //esto hay q cambiarlo a una posicion random por delante
		if (obj.type == 1) {
			sp.suelo->setGlobalPose({ sp.suelo->getGlobalPose().p.x,sp.suelo->getGlobalPose().p.y, newPos.z + ELASTIC_BED_SIZE.z_/2 });
		}
		obstaculos.pop();
		obstaculos.push(obj);
	}
}

void ObstacleManager::checkElasticBed()
{
	if (checkDistanceBtwChar(sp.suelo->getGlobalPose().p.z + 40)) {
		ch->setNewJumpForce(IN_JUMP_FORCE * 2);
	}
	else {
		ch->setNewJumpForce(IN_JUMP_FORCE);
	}
}

void ObstacleManager::generateSpecialObstacle()
{
	sp = SpecialObstacle(generateStaticElement({ 0, 0, -1300 }, shape_, { 50, 70, 10 }), generateStaticElement({ 0, 14.5, -1280 }, shape_, ELASTIC_BED_SIZE));
	obstaculos.push(sp);
}

void ObstacleManager::generateFloor()
{
	//genera el suelo....
	floor = generateStaticElement({ 0, 15, 0 }, Particle::Box, FLOOR_SIZE, {1, 1, 1, 1});
}

ObstacleManager::ObstacleManager(): IN_JUMP_FORCE(0)
{
}


ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::update(float t)
{
	checkFloor();
	checkObstacle();
	checkElasticBed();
}
