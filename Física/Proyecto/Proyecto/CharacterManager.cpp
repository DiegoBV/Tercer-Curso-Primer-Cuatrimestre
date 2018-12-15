#include "CharacterManager.h"

void CharacterManager::checkIfPJisDead()
{
	Vector3 pos = chr->getPj()->getGlobalPose().p;
	physx::PxVec3 eye = GetCamera()->getEye();
	int f_W = FLOOR_SIZE.x_ + FLOOR_SIZE.x_/4;
	int f_H = FLOOR_POS.y - FLOOR_POS.y / 6;

	if (fabs(pos.y) > eye.x + f_W && (pos.y) < f_H || eye.z < (pos.z + DIST_TO_CHECK_)) {
		chr->setDead(true);
		death_count++;
		mciSendString("play ../Sonidos/fail.wav", NULL, 0, NULL);
	}
}

void CharacterManager::resCharacter(float t)
{
	if (chr->isDead()) {
		time_passed_ += t;
		if (time_passed_ >= DELAY_) {
			physx::PxVec3 eye = GetCamera()->getEye();
			chr->getPj()->setGlobalPose({ initial_pos.x, initial_pos.y + 50, eye.z + DIST_TO_CAMERA_ });
			chr->getPj()->clearForce();
			chr->getPj()->clearTorque();
			chr->getPj()->setLinearVelocity({ 0, 0, 0 });
			chr->setDead(false);
			time_passed_ = 0;
		}
	}
}

void CharacterManager::update(float t)
{
	chr->getPj()->setLinearVelocity({ chr->getPj()->getLinearVelocity().x, chr->getPj()->getLinearVelocity().y, -velocity_ });
	checkIfPJisDead();
	if (isDebugging()) {     //solo para ensenyar el funcionamiento de los obstaculos, se puede eliminar
		chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x, 80, chr->getPj()->getGlobalPose().p.z });
	}
}

void CharacterManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case ' ':
		if(chr->canThisJump()){																												//if ((int)chr->getPj()->getGlobalPose().p.y == (int)initial_pos.y) { //mmmm alguna forma de saber si esta en contacto con el suelo...??
			chr->getPj()->setLinearVelocity({ chr->getPj()->getLinearVelocity().x, chr->getJumpForce(), chr->getPj()->getLinearVelocity().z });
			chr->setCanJump(false);
			mciSendString("play ../Sonidos/jumpEffect.wav", NULL, 0, NULL);
		}
		break;
	case 'W':
		chr->getPj()->setLinearVelocity({ 0, chr->getPj()->getLinearVelocity().y, -velocity_ });
		break;
	case 'A':
		chr->getPj()->setLinearVelocity({-velocity_/4, chr->getPj()->getLinearVelocity().y, -velocity_}); //improve del gameplay maybe
		break;
	case 'D':
		chr->getPj()->setLinearVelocity({ velocity_/4, chr->getPj()->getLinearVelocity().y, -velocity_ });
		break;
	default:
		break;
	}
}
