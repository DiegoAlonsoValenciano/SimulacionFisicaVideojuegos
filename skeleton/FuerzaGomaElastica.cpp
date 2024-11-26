#include "FuerzaGomaElastica.h"

FuerzaGomaElastica::FuerzaGomaElastica(double _k, double _distancia_reposo, Particle* _otra)
	:k(_k), distancia_reposo(_distancia_reposo), otra(_otra)
{}

void FuerzaGomaElastica::update(Particle* p, double t) {
	Vector3 relative_pos_vector = otra->GetPos() - p->GetPos();

	if (relative_pos_vector.magnitude() > distancia_reposo) {
		float lenght = relative_pos_vector.normalize();
		float delta_x = lenght - distancia_reposo;

		fuerza = relative_pos_vector * delta_x * k;

		p->updateForce(fuerza);
	}
}

