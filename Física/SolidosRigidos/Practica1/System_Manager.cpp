#include "System_Manager.h"



Vector3 System_Manager::generateRandomVel()
{
	Vector3 nVel = { (float)(rand() % (VEL_MAX_)-VEL_MAX_ / 2), (float)(VEL_MIN_ + rand() % (VEL_MAX_ - VEL_MIN_)), (float)(rand() % (VEL_MAX_)-VEL_MAX_ / 2) }; //esto es para que salgan tipo fuente y se observe la gravedad bien
	return nVel;
}

Vector4 System_Manager::generateRandomColor()
{
	Vector4 nCol = { (float)(rand() % (11)) / 10, (float)(rand() % (11)) / 10 , (float)(rand() % (11)) / 10, 1 };
	return nCol;
}

void System_Manager::handle_event(unsigned char key)
{
	//do something
	switch (toupper(key))
	{
	case 'T':
		setOn(!on);
		break;
	default:
		break;
	}
}
