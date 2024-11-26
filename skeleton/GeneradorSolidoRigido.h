#pragma once

#include "SolidoRigido.h"
#include <list>
#include <random>

using namespace std;

class GeneradorSolidoRigido
{
public:
	GeneradorSolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite);
	~GeneradorSolidoRigido();
	virtual void update() = 0;
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
};

