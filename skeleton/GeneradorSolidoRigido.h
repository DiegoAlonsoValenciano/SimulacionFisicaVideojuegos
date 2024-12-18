#pragma once

#include "SolidoRigido.h"
#include <list>
#include <random>
#include "SolidForceRegister.h"
#include "SolidForceGenerator.h"

using namespace std;

class GeneradorSolidoRigido
{
public:
	GeneradorSolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r);
	~GeneradorSolidoRigido();
	virtual void update() = 0;
	void addFuerza(SolidForceGenerator* f);
	void quitarFuerza(SolidForceGenerator* f);
	void destruir(physx::PxActor* actor);
protected:
	PxScene* gScene;
	PxPhysics* gPhysics;
	Vector3 fuente;
	list<SolidoRigido*> lista;
	int rango;
	int limite;
	mt19937_64 randomGenerator;
	float x;
	float y;
	float z;
	float xl;
	float yl;
	float zl;
	float xa;
	float ya;
	float za;
	float tv;
	virtual void generateRandom() = 0;
	list<SolidForceGenerator*> fuerzas;
	SolidForceRegister* registro;
};

