#include "SolidSeguirForce.h"

SolidSeguirForce::SolidSeguirForce(float vel, SolidoRigido* obj) 
	:vel(vel),objetivo(obj)
{

}

void SolidSeguirForce::update(SolidoRigido* s) {
	Vector3 dir = (objetivo->GetPos() - s->GetPos()).getNormalized();
	fuerza = dir * vel;
	s->addForce(fuerza);
}
