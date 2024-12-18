#pragma once
#include "SolidoRigido.h"
#include "GenerarBala.h"
#include "SolidForceRegister.h"
#include "SolidForceGenerator.h"

class ConejoAlien: public SolidoRigido
{
public:
	ConejoAlien(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, SolidForceRegister* r);
	~ConejoAlien();
	void disparar();
	void salto(Vector3 dir);
	void update();
protected:
	GenerarBala* pistola = nullptr;
	int vel = 70;
	Vector3 direccion;
};

