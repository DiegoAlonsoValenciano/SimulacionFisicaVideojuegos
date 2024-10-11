#pragma once

#include "Particle.h"
#include <list>
#include <random>

using namespace std;

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3 fuente, int rango);
	void update(double t);
private:
	Vector3 fuente;
	list<Particle*> lista;
	int rango;
	mt19937_64 randomGenerator;
};

