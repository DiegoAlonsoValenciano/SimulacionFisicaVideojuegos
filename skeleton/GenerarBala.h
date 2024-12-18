#pragma once
#include "GeneradorSolidoRigido.h"

class GenerarBala:public GeneradorSolidoRigido
{
public:
	GenerarBala(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r);
	virtual void update() override;
	void disparo(Vector3 pos, Vector3 dir);
protected:
	virtual void generateRandom() override;
	int vel = 200;
};

