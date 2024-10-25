#include "FuerzaGravedad.h"

FuerzaGravedad::FuerzaGravedad() {
	fuerza = Vector3({ 0,-9.8,0 });
}

void FuerzaGravedad::update(Particle* p) {
	p->updateForce(fuerza);
}
