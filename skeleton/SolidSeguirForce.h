#pragma once
#include "SolidForceGenerator.h"

class SolidSeguirForce: public SolidForceGenerator
{
public:
	SolidSeguirForce(float vel, SolidoRigido* obj);
	virtual void update(SolidoRigido* s) override;
protected:
	float vel;
	SolidoRigido* objetivo = nullptr;
};

