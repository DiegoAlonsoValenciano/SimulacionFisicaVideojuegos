#include "FuerzaGravedad.h"

FuerzaGravedad::FuerzaGravedad() :ForceGenerator({0,-9.8,0})
{}

void FuerzaGravedad::update(Particle* p) {
	p->updateForce(fuerza);
}
