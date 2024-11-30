#include "SolidoRigido.h"

SolidoRigido::SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d)
	:gScene(gScene), gPhysics(gPhysics), tiempoVida(0), tiempo(5000)
{
	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	shape_ad = CreateShape(PxBoxGeometry(1, 1, 1));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, d);
	gScene->addActor(*new_solid);
	dynamic_item = new RenderItem(shape_ad, new_solid, { 1.0,0.0,0.0,1.0 });
}

SolidoRigido::SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin)
	:gScene(gScene), gPhysics(gPhysics), tiempoVida(0), tiempo(5000)
{
	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(velLin);
	new_solid->setAngularVelocity({ 0,0,0 });
	shape_ad = CreateShape(PxBoxGeometry(1, 1, 1));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, d);
	gScene->addActor(*new_solid);
	dynamic_item = new RenderItem(shape_ad, new_solid, { 1.0,0.0,0.0,1.0 });
}

SolidoRigido::SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin, Vector3 velAng)
	:gScene(gScene), gPhysics(gPhysics), tiempoVida(0), tiempo(5000)
{
	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(velLin);
	new_solid->setAngularVelocity(velAng);
	shape_ad = CreateShape(PxBoxGeometry(1, 1, 1));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, d);
	gScene->addActor(*new_solid);
	dynamic_item = new RenderItem(shape_ad, new_solid, { 1.0,0.0,0.0,1.0 });
}

SolidoRigido::SolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, double d, Vector3 velLin, Vector3 velAng, Vector3 dim)
	:gScene(gScene), gPhysics(gPhysics), tiempoVida(0), tiempo(5000)
{
	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(velLin);
	new_solid->setAngularVelocity(velAng);
	shape_ad = CreateShape(PxBoxGeometry(dim));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, d);
	gScene->addActor(*new_solid);
	dynamic_item = new RenderItem(shape_ad, new_solid, { 1.0,0.0,0.0,1.0 });
}

SolidoRigido::~SolidoRigido() {
	gScene->removeActor(*new_solid);
	DeregisterRenderItem(dynamic_item);
}

bool SolidoRigido::update() {
	tiempoVida++;
	if (tiempoVida > tiempo) {
		return true;
	}
	else {
		return false;
	}
}

void SolidoRigido::setColor(Vector4 color) {
	dynamic_item->color = color;
}

void SolidoRigido::setTiempoVida(float tv) {
	tiempo = tv;
}

void SolidoRigido::addForce(Vector3 fuerza) {
	new_solid->addForce(fuerza);
}

Vector3 SolidoRigido::GetPos() const {
	return new_solid->getGlobalPose().p;
}

Vector3 SolidoRigido::GetVel() const {
	return new_solid->getLinearVelocity();
}

double SolidoRigido::GetMasa() const {
	return new_solid->getMass();
}