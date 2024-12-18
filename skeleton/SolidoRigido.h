#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
#include <iostream>

using namespace physx;
using namespace std;

class SolidoRigido
{
public:
	SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d);
	SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin);
	SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin, Vector3 velAng);
	SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin, Vector3 velAng, Vector3 dim);
	SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin, Vector3 velAng, float tamesf);
	~SolidoRigido();
	bool update();
	void setColor(Vector4 color);
	void setTiempoVida(float tv);
	void addForce(Vector3 fuerza);
	Vector3 GetPos() const;
	Vector3 GetVel() const;
	double GetMasa() const;
	void setName(const char* nombre);
	void Matar();
	void setTensorInercia(Vector3 TI);
	PxRigidDynamic* getActor();
protected:
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxRigidDynamic* new_solid;
	PxShape* shape_ad;
	RenderItem* dynamic_item;
	int tiempoVida;
	int tiempo;
	bool matar = false;
};

