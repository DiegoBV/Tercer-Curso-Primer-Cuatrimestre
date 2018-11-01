#pragma once
#include "TemplatePool.h"

class Manager
{
public:
	Manager() {};
	virtual ~Manager() {};
	virtual void update(double t) = 0;                        //virtual para poder llamarlo con vectores, update
	virtual void handle_event(unsigned char key) = 0;         //virtual para poder llamarlo con vectores, handle_event
};

