#pragma once

#include "Particle.h"
#include <list>
#include <random>
#include "ParticleForceRegister.h"
#include "ForceGenerator.h"

using namespace std;

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3 fuente, int rango, ParticleForceRegister* r);
	~ParticleGenerator();
	virtual void update(double t) = 0;
	void addFuerza(ForceGenerator* f);
	void quitarFuerza(ForceGenerator* f);
	void setColor(Vector4 c);
	void setTam(float t);
protected:
	Vector3 fuente;
	list<Particle*> lista;
	int rango;
	mt19937_64 randomGenerator;
	float x;
	float y;
	float z;
	float tv;
	virtual void generateRandom() = 0;
	list<ForceGenerator*> fuerzas;
	ParticleForceRegister* registro;
	Vector4 color;
	float tam;
};

