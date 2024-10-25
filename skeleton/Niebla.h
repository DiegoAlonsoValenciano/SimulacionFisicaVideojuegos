#pragma once

#include "ParticleGenerator.h"

class Niebla : public ParticleGenerator
{
public:
	Niebla(Vector3 fuente, float radio, ParticleForceRegister* r);
	virtual void update(double t) override;
protected:
	virtual void generateRandom() override;
	float fx;
	float fy;
	float fz;
	float radio;
};

