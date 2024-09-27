#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel)
	:vel(Vel), pose(Pos), acel({0,0,0}), damping(0.998)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel)
	:vel(Vel), pose(Pos), acel(Acel), damping(0.998)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double d)
	:vel(Vel), pose(Pos), acel(Acel), damping(d)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t) {
	vel = vel + acel * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + vel * t;
}