#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
#include <map>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"


class ParticleForceRegister
{
public:
	ParticleForceRegister();
	void Registrar(ForceGenerator* f, Particle* p);
	void LiberarFuerza(ForceGenerator* f);
	void LiberarParticula(Particle* p);
	void update();
protected:
	multimap<ForceGenerator*, Particle*> fuerzas;
};

