#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class FuerzaMuelle :public ForceGenerator
{
public:
	FuerzaMuelle(double _k, double _distancia_reposo, Particle* _otra);
	virtual void update(Particle* p, double t) override;
	void setK(double _k) { k = _k; };

private:
	double k;
	double distancia_reposo;
	Particle* otra;
};

