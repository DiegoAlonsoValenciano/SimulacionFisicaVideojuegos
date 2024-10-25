#include "Particle.h"

Particle::Particle()
	:vel({0,0,0}), pose({0,0,0}), acel({0,0,0}), damping(0.998), tiempoVida(0), tiempo(5000), euler(true), masa(0.000000000001), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel)
	:vel(Vel), pose(Pos), acel({0,0,0}), damping(0.998), tiempoVida(0), tiempo(5000), euler(true), masa(0.000000000001), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double m)
	:vel(Vel), pose(Pos), acel({ 0,0,0 }), damping(0.998), tiempoVida(0), tiempo(5000), euler(true), masa(m), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel)
	:vel(Vel), pose(Pos), acel(Acel), damping(0.998), tiempoVida(0), tiempo(5000), euler(true), masa(m), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel, double d)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(5000), euler(true), masa(m), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double m, Vector3 Acel, double d, float tam)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(5000), euler(true), masa(m), acFuerza({ 0,0,0 })
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

bool Particle::integrate(double t) {
	if (euler) {
		acel = acFuerza/masa;
		vel = vel + acel * t;
		vel = vel * pow(damping, t);
		pose.p = pose.p + vel * t;
	}
	else {
		vel = vel + acel * t;
		vel = vel * pow(damping, t);
		pose.p = pose.p + vel * t + 0.5 * acel * pow(t, 2);
	}
	tiempoVida++;
	if (tiempoVida > tiempo) {
		return true;
	}
	else {
		return false;
	}
	acFuerza = Vector3({ 0,0,0 });
}

void Particle::setColor(Vector4 color) {
	renderItem->color = color;
}

void Particle::setTiempoVida(float tv) {
	tiempo = tv;
}

void Particle::setEuler(bool elr) {
	euler = elr;
}

void Particle::updateForce(Vector3 plusForce) {
	acFuerza += plusForce;
}

Vector3 Particle::GetPos() const {
	return pose.p;
}

Vector3 Particle::GetVel() const {
	return vel;
}