#include "SolidFuerzaMuelleFijo.h"

SolidFuerzaMuelleFijo::SolidFuerzaMuelleFijo(double _k, double _distancia_reposo, Vector3 _ancla)
	:k(_k), distancia_reposo(_distancia_reposo), ancla(_ancla), pose(_ancla)
{
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(1, 1, 1)), &pose, { 0.9, 0.9, 0.9, 1.0 });
}

SolidFuerzaMuelleFijo::~SolidFuerzaMuelleFijo() {
	DeregisterRenderItem(renderItem);
}

void SolidFuerzaMuelleFijo::update(SolidoRigido* s) {
	Vector3 relative_pos_vector = ancla - s->GetPos();

	float lenght = relative_pos_vector.normalize();
	float delta_x = lenght - distancia_reposo;

	fuerza = relative_pos_vector * delta_x * k;

	s->addForce(fuerza);
}
