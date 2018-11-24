#include "CharacterManager.h"

void CharacterManager::update(double t)
{
}

void CharacterManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'W':
	{
		chr->getPj()->setLinearVelocity({ 0, 0, -velocity_ });
		/*Vector3 f = GetCamera()->getEye();        //pffffffffffffffffff
		f -= chr->getPosition();
		// Length
		float length = f.normalize();
		if ((int)length >= (int)67) {
			// Resulting force
			f *= -((length) * 2);
			GetCamera()->move(2);
		}*/
	}
		break;
	case 'S':
		chr->getPj()->setLinearVelocity({ 0, 0, velocity_ });
		break;
	case 'A':
		chr->getPj()->setLinearVelocity({ -velocity_, 0, 0 });
		break;
	case 'D':
		chr->getPj()->setLinearVelocity({ velocity_, 0, 0 });
		break;
	default:
		break;
	}
}
