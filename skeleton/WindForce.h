#pragma once
#include "ForceGenerator.h"

class WindForce: public ForceGenerator
{
public:
	WindForce(Vector3 v, Vector3 orig, int area);
	virtual void update(Particle* p, double t) override;
protected:
	Vector3 vel;
	Vector3 origen;
	int area;
};

