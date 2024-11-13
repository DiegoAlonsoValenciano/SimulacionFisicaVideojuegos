#include "FuerzaExplosion.h"

FuerzaExplosion::FuerzaExplosion(Vector3 orig, int area):origen(orig),area(area)
{}

void FuerzaExplosion::update(Particle* p,double t) {
	if ((p->GetPos() - origen).magnitude() <= area) {
		fuerza = (1000 / pow(area, 2)) * Vector3({ p->GetPos().x - origen.x,p->GetPos().y - origen.y,p->GetPos().z - origen.z }) * exp(-(t/4));
		p->updateForce(fuerza);
	}
}