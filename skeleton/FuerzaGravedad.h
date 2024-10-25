#pragma once
#include "ForceGenerator.h"

class FuerzaGravedad: public ForceGenerator
{
public:
	FuerzaGravedad();
	virtual void update(Particle* p) override;
};

