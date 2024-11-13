#pragma once
#include "ForceGenerator.h"
#include <cmath>

class FuerzaExplosion : public ForceGenerator
{
public:
	FuerzaExplosion(Vector3 orig, int area);
	virtual void update(Particle* p, double t) override;
private:
	Vector3 origen;
	int area;
};

