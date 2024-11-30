#pragma once
#include "GeneradorSolidoRigido.h"

class SolidParty:public GeneradorSolidoRigido
{
public:
	SolidParty(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r);
	virtual void update() override;
protected:
	virtual void generateRandom() override;
	float r;
	float g;
	float b;
};

