#pragma once

#include"Particle.h"

class Proyectil:public Particle
{
public:
	Proyectil(Vector3 Pos, Vector3 Vel, int m);

	virtual void integrate(double t) override;
protected:
	int masa;
	Vector3 velS;
	int masaS;
	Vector3 acelS;

};

