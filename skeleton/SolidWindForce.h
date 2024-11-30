#pragma once
#include "SolidForceGenerator.h"

class SolidWindForce: public SolidForceGenerator
{
public:
	SolidWindForce(Vector3 v, Vector3 orig, int area);
	virtual void update(SolidoRigido* s) override;
protected:
	Vector3 vel;
	Vector3 origen;
	int area;
};

