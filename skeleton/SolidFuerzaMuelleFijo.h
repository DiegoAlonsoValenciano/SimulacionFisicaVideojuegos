#pragma once
#include "SolidForceGenerator.h"

class SolidFuerzaMuelleFijo:public SolidForceGenerator
{
public:
	SolidFuerzaMuelleFijo(double _k, double _distancia_reposo, Vector3 _ancla);
	~SolidFuerzaMuelleFijo();
	virtual void update(SolidoRigido* s) override;
	void setK(double _k) { k = _k; };

private:
	double k;
	double distancia_reposo;
	Vector3 ancla;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que actualice automaticamente
	RenderItem* renderItem;
};

