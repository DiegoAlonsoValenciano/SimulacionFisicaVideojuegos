#pragma once

#include "ParticleGenerator.h"

class Party:public ParticleGenerator
{
public:
	Party(Vector3 fuente, float radio, ParticleForceRegister* r);
	virtual void update(double t) override;
protected:
	virtual void generateRandom() override;
	float r;
	float g;
	float b;
};

