#include "ObstacleManager.h"



void ObstacleManager::generateObstacle()
{
	obstaculos.push(generateStaticElement({ 0, 0, 0 }, shape_, {10, 10, 10})); //puedo especificarle tamanyo y eso
}

void ObstacleManager::reparteObstaculos()
{
	float z = dis_between_obs;
	for (size_t i = 0; i < MAX_OBS; i++){
		physx::PxRigidStatic* obj = obstaculos.front();
		obstaculos.pop();
		Vector3 pos = generateRandomPos({ 0, 0, 4000 }, dis_between_obs, FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2);
		obj->setGlobalPose({ pos.x, 20, z });
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
	physx::PxRigidStatic* obj = obstaculos.front();

	if (checkDistanceBtwChar(obj->getGlobalPose().p.z - dis_between_obs)) {
		Vector3 newPos = generateRandomPos(obj->getGlobalPose().p, dis_between_obs * MAX_OBS, FLOOR_SIZE.x_ / 2, -FLOOR_SIZE.x_ / 2);
		obj->setGlobalPose({newPos.x, newPos.y, newPos.z}); //esto hay q cambiarlo a una posicion random por delante
		obstaculos.pop();
		obstaculos.push(obj);
	}
}

void ObstacleManager::generateFloor()
{
	//genera el suelo....
	floor = generateStaticElement({ 0, 15, 0 }, Particle::Box, FLOOR_SIZE, {1, 1, 1, 1});
}

ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::update(float t)
{
	checkFloor();
	checkObstacle();
}
