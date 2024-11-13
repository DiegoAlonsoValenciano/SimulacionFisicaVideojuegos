#include "FuerzaTorbellino.h"

FuerzaTorbellino::FuerzaTorbellino(Vector3 orig, int area) :WindForce({0,0,0}, orig, area)
{}

void FuerzaTorbellino::update(Particle* p, double t) {
	if ((p->GetPos() - origen).magnitude() <= area) {
		vel = 10 * (Vector3({ -(p->GetPos().z - origen.z),50 - (p->GetPos().y - origen.y),p->GetPos().x - origen.x }));

		fuerza = (0.25 * (vel - p->GetVel())) + (0 * ((vel - p->GetVel()).magnitude()) * (vel - p->GetVel()));
		p->updateForce(fuerza);
	}
	
}
