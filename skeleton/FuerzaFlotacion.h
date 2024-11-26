#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class FuerzaFlotacion :public ForceGenerator
{
public:
	FuerzaFlotacion(float h, float V, float d, Vector3 superficie);
	~FuerzaFlotacion();
	virtual void update(Particle* p, double t) override;
private:
	float altura;
	float volumen;
	float densidad_liquido;
	float gravedad = 9.8;
	Vector3 pos;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que actualice automaticamente
	RenderItem* renderItem;

};

