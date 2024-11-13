#pragma once
#include "ParticleGenerator.h"

class MuchasParticulas :public ParticleGenerator
{
public:
	MuchasParticulas(Vector3 fuente, float radio, ParticleForceRegister* r);
	virtual void update(double t) override;
protected:
	virtual void generateRandom() override;
};

