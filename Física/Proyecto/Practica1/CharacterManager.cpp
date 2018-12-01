#include "CharacterManager.h"

void CharacterManager::update(float t)
{
}

void CharacterManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'A':
		chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x - 20 , chr->getPj()->getGlobalPose().p.y,  chr->getPj()->getGlobalPose().p.z});
		//chr->getPj()->setLinearVelocity({velocity_, 0, -velocity_}); //improve del gameplay maybe
		break;
	case 'D':
		chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x + 20 , chr->getPj()->getGlobalPose().p.y,  chr->getPj()->getGlobalPose().p.z });
		break;
	case ' ':
		if((int)chr->getPj()->getGlobalPose().p.y == (int)initial_pos.y) //mmmm alguna forma de saber si esta en contacto con el suelo...??
			chr->getPj()->setLinearVelocity({chr->getPj()->getLinearVelocity().x, JUMP_FORCE, chr->getPj()->getLinearVelocity().z});
		break;
	default:
		break;
	}
}
