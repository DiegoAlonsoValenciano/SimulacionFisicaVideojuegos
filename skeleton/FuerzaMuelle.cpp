#include "FuerzaMuelle.h"

FuerzaMuelle::FuerzaMuelle(double _k, double _distancia_reposo, Particle* _otra)
	:k(_k),distancia_reposo(_distancia_reposo),otra(_otra)
{}

void FuerzaMuelle::update(Particle* p, double t) {
	Vector3 relative_pos_vector = otra->GetPos() - p->GetPos();

	float lenght = relative_pos_vector.normalize();
	float delta_x = lenght - distancia_reposo;

	fuerza = relative_pos_vector * delta_x * k;

	p->updateForce(fuerza);
}
