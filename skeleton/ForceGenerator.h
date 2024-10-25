#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator();
	virtual void update(Particle* p) = 0;
protected:
	Vector3 fuerza;
};

