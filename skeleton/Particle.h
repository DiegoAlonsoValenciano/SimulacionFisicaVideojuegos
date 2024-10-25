#pragma once
#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>

using namespace physx;

class Particle
{
public:
	Particle();
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, double m);
	Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel);
	Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel, double d);
	Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel, double d, float tam);
	~Particle();

	virtual bool integrate(double t);
	void setColor(Vector4 color);
	void setTiempoVida(float tv);
	void setEuler(bool elr);
	void updateForce(Vector3 plusForce);
	Vector3 GetPos() const;
	Vector3 GetVel() const;
protected:
	Vector3 vel;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que actualice automaticamente
	RenderItem* renderItem;
	Vector3 acel;
	double damping;
	int tiempoVida;
	int tiempo;
	bool euler;
	double masa;
	Vector3 acFuerza;
};

