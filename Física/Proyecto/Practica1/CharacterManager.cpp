#include "CharacterManager.h"

void CharacterManager::update(float t)
{
	chr->getPj()->setLinearVelocity({ chr->getPj()->getLinearVelocity().x, chr->getPj()->getLinearVelocity().y, -velocity_ });
}

void CharacterManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case ' ':
		if((int)chr->getPj()->getGlobalPose().p.y == (int)initial_pos.y) //mmmm alguna forma de saber si esta en contacto con el suelo...??
			chr->getPj()->setLinearVelocity({chr->getPj()->getLinearVelocity().x, chr->getJumpForce(), chr->getPj()->getLinearVelocity().z});
		break;
	case 'W':
		chr->getPj()->setLinearVelocity({ 0, chr->getPj()->getLinearVelocity().y, -velocity_ });
		break;
	case 'A':
		//chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x - 20 , chr->getPj()->getGlobalPose().p.y,  chr->getPj()->getGlobalPose().p.z});
		chr->getPj()->setLinearVelocity({-velocity_/4, chr->getPj()->getLinearVelocity().y, -velocity_}); //improve del gameplay maybe
		break;
	case 'D':
		//chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x + 20 , chr->getPj()->getGlobalPose().p.y,  chr->getPj()->getGlobalPose().p.z });
		chr->getPj()->setLinearVelocity({ velocity_/4, chr->getPj()->getLinearVelocity().y, -velocity_ });
		break;
	default:
		break;
	}
}
