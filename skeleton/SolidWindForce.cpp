#include "SolidWindForce.h"

SolidWindForce::SolidWindForce(Vector3 v, Vector3 orig, int area) :vel(v), origen(orig), area(area)
{}

void SolidWindForce::update(SolidoRigido* s) {
	if ((s->GetPos() - origen).magnitude() <= area) {
		fuerza = (0.25 * (vel - s->GetVel())) + (0 * ((vel - s->GetVel()).magnitude()) * (vel - s->GetVel()));
		s->addForce(fuerza);
	}

}
