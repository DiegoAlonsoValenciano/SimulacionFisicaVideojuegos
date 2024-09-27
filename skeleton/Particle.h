#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que actualice automaticamente
	RenderItem* renderItem;
	Vector3 acel;
	double damping;
};

