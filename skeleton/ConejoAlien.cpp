#include "ConejoAlien.h"

ConejoAlien::ConejoAlien(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, SolidForceRegister* r)
	:SolidoRigido(gScene,gPhysics,pos, 1, { 0,5,0 }, { 0,0,0 }, { 4,4,4 })
{
	setColor({ 0.0,1.0,0.0,1.0 });
	pistola = new GenerarBala(gScene, gPhysics, { 0,0,0 }, 300, 10, r);
	direccion = Vector3(0, 0, -1);
	setName("conejo");
	float I = (1 / 12) * 1 * (pow(4, 2) + pow(4, 2));
	setTensorInercia(Vector3(I, I, I));
}

ConejoAlien::~ConejoAlien() {
	delete pistola;
}

void ConejoAlien::disparar() {
	pistola->disparo(GetPos()+(direccion*4),direccion);
}

void ConejoAlien::salto(Vector3 dir) {
	direccion = dir;
	new_solid->setLinearVelocity(dir*vel);
}

void ConejoAlien::update() {
	pistola->update();
}