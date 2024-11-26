#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class FuerzaMuelleFijo :public ForceGenerator
{
public:
	FuerzaMuelleFijo(double _k, double _distancia_reposo, Vector3 _ancla);
	~FuerzaMuelleFijo();
	virtual void update(Particle* p, double t) override;
	void setK(double _k) { k = _k; };

private:
	double k;
	double distancia_reposo;
	Vector3 ancla;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que actualice automaticamente
	RenderItem* renderItem;
};

