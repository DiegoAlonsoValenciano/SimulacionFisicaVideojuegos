#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
#include "SolidoRigido.h"

using namespace std;

class SolidForceGenerator
{
public:
	SolidForceGenerator();
	virtual void update(SolidoRigido* s) = 0;
protected:
	Vector3 fuerza;
};

