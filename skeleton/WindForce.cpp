#include "WindForce.h"

WindForce::WindForce(Vector3 v, Vector3 orig, int area):vel(v), origen(orig), area(area)
{}

void WindForce::update(Particle* p, double t) {
	if ((p->GetPos() - origen).magnitude() <= area) {
		fuerza = (0.25 * (vel - p->GetVel()));
		p->updateForce(fuerza);
	}
	
}