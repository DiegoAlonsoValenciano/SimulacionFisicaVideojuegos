#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
#include <map>
#include "SolidoRigido.h"
#include "SolidForceGenerator.h"
#include <list>
#include <random>

class SolidForceRegister
{
public:
	SolidForceRegister();
	void Registrar(SolidForceGenerator* f, SolidoRigido* s);
	void LiberarFuerza(SolidForceGenerator* f);
	void LiberarSolido(SolidoRigido* s);
	void update();
protected:
	multimap <SolidForceGenerator*, SolidoRigido*> fuerzas;
};

