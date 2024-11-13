#pragma once
#include "ForceGenerator.h"
#include "WindForce.h"

class FuerzaTorbellino : public WindForce
{
public:
	FuerzaTorbellino(Vector3 orig, int area);
	virtual void update(Particle* p, double t) override;
protected:
};

