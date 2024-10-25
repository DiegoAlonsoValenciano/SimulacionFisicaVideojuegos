#pragma once

#include"Particle.h"

class Proyectil:public Particle
{
public:
	Proyectil(Vector3 Pos, Vector3 Vel, double m);

	virtual bool integrate(double t) override;
protected:
	Vector3 velS;
	int masaS;
	Vector3 acelS;

};

