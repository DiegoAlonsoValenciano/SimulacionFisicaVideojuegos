#include "FuerzaFlotacion.h"

FuerzaFlotacion::FuerzaFlotacion(float h, float V, float d, Vector3 superficie)
	:altura(h), volumen(V), densidad_liquido(d), pos(superficie), pose(superficie)
{
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(33, 0.1, 1)), &pose, { 0.0, 0.5, 1.0, 1.0 });
}

FuerzaFlotacion::~FuerzaFlotacion() {
	DeregisterRenderItem(renderItem);
}

void FuerzaFlotacion::update(Particle* p, double t) {
	float h = p->GetPos().y;
	float h0 = pos.y;

	float sumergido = 0.0;
	if (h - h0 > altura * 0.5) {
		sumergido = 0.0;
	}
	else if (h0 - h > altura * 0.5) {
		sumergido = 1.0;
	}
	else {
		sumergido = (h0 - h) / altura + 0.5;
	}
	fuerza = Vector3(0, densidad_liquido * volumen * sumergido * gravedad, 0);
	p->updateForce(fuerza);
}