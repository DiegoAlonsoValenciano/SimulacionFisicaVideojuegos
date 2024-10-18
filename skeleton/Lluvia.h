#pragma once

#include "ParticleGenerator.h"

class Lluvia: public ParticleGenerator
{
public:
	Lluvia(Vector3 fuente, float radio);
	virtual void update(double t) override;
protected:
	virtual void generateRandom() override;
	float fx;
	float fz;
	float radio;
};

