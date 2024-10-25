#include "Proyectil.h"

Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, double m)
	:Particle(Pos, Vel, m, { 0,-9.8,0 }, 1)
{
	velS = vel.getNormalized() * 25;
	masaS = masa * (pow(vel.magnitude()/velS.magnitude(),2));
	acelS = acel * (pow(velS.magnitude() / vel.magnitude(), 2));
}

bool Proyectil::integrate(double t) {

	acelS = acFuerza / masaS;
	velS = velS + acelS * t;
	velS = velS * pow(damping, t);
	pose.p = pose.p + velS * t + 0.5*acelS*pow(t,2);
	tiempoVida++;
	if (tiempoVida > 5000) {
		return true;
	}
	else {
		return false;
	}
	acFuerza = Vector3({ 0,0,0 });
}