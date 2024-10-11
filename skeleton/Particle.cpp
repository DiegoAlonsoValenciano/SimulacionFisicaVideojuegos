#include "Particle.h"

Particle::Particle()
	:vel({0,0,0}), pose({0,0,0}), acel({0,0,0}), damping(0.998), tiempoVida(0), tiempo(5000)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel)
	:vel(Vel), pose(Pos), acel({0,0,0}), damping(0.998), tiempoVida(0), tiempo(5000)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel)
	:vel(Vel), pose(Pos), acel(Acel), damping(0.998), tiempoVida(0), tiempo(5000)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(5000)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d, float tam)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(5000)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d, int tv)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(tv)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d, float tam, int tv)
	:vel(Vel), pose(Pos), acel(Acel), damping(d), tiempoVida(0), tiempo(tv)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

bool Particle::integrate(double t) {
	vel = vel + acel * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + vel * t;
	tiempoVida++;
	if (tiempoVida > tiempo) {
		return true;
	}
	else {
		return false;
	}
}

void Particle::setColor(Vector4 color) {
	renderItem->color = color;
}

Vector3 Particle::GetPos() {
	return pose.p;
}