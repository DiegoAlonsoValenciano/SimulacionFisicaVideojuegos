#pragma once
#include "GeneradorSolidoRigido.h"

class GenerarEnemigo:public GeneradorSolidoRigido
{
public:
	GenerarEnemigo(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r);
	virtual void update() override;
protected:
	virtual void generateRandom() override;
};

