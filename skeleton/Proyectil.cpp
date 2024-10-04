#include "Proyectil.h"

Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, int m)
	:Particle(Pos, Vel, { 0,-9.8,0 }, 1), masa(m)
{
	velS = vel.getNormalized() * 25;
	masaS = masa * (pow(vel.magnitude()/velS.magnitude(),2));
	acelS = acel * (pow(velS.magnitude() / vel.magnitude(), 2));
}

void Proyectil::integrate(double t) {
	velS = velS + acelS * t;
	velS = velS * pow(damping, t);
	pose.p = pose.p + velS * t + 0.5*acelS*pow(t,2);
}