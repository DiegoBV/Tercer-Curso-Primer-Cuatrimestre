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
		//chr->getPj()->setLinearVelocity(...); improve del gameplay maybe
		break;
	case 'D':
		chr->getPj()->setGlobalPose({ chr->getPj()->getGlobalPose().p.x + 20 , chr->getPj()->getGlobalPose().p.y,  chr->getPj()->getGlobalPose().p.z });
		break;
	default:
		break;
	}
}
