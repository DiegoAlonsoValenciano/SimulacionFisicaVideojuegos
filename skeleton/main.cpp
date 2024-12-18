#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <map>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "Proyectil.h"
#include "ParticleGenerator.h"
#include "Lluvia.h"
#include "Niebla.h"
#include "Party.h"
#include "ForceGenerator.h"
#include "ParticleForceRegister.h"
#include "FuerzaGravedad.h"
#include "WindForce.h"
#include "FuerzaTorbellino.h"
#include "FuerzaExplosion.h"
#include "MuchasParticulas.h"
#include "FuerzaMuelle.h"
#include "FuerzaMuelleFijo.h"
#include "FuerzaFlotacion.h"
#include "FuerzaGomaElastica.h"
#include "SolidoRigido.h"
#include "GeneradorSolidoRigido.h"
#include "SolidParty.h"
#include "SolidForceGenerator.h"
#include "SolidForceRegister.h"
#include "SolidWindForce.h"
#include "GenerarBala.h"
#include "ConejoAlien.h"
#include "SolidSeguirForce.h"
#include "SolidFuerzaMuelleFijo.h"
#include "GenerarEnemigo.h"

#include <map>

std::string display_text = "This is a test";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Lluvia* lluvia = nullptr;
ParticleForceRegister* registroF = nullptr;
FuerzaGravedad* gravedad = nullptr;
WindForce* viento = nullptr;
SolidForceRegister* registroS = nullptr;
Lluvia* lluvia2 = nullptr;

PxRigidStatic* suelo;
RenderItem* item;
PxRigidStatic* muro1;
RenderItem* item1;
PxRigidStatic* muro2;
RenderItem* item2;
PxRigidStatic* muro3;
RenderItem* item3;
PxRigidStatic* muro4;
RenderItem* item4;
ConejoAlien* conejoAlien = nullptr;
SolidSeguirForce* solidSeguirForce = nullptr;
SolidFuerzaMuelleFijo* solidFuerzaMuelleFijo1 = nullptr;
SolidFuerzaMuelleFijo* solidFuerzaMuelleFijo2 = nullptr;
SolidFuerzaMuelleFijo* solidFuerzaMuelleFijo3 = nullptr;
SolidFuerzaMuelleFijo* solidFuerzaMuelleFijo4 = nullptr;
SolidoRigido* enemigoP1 = nullptr;
SolidoRigido* enemigoP2 = nullptr;
SolidoRigido* enemigoP3 = nullptr;
SolidoRigido* enemigoP4 = nullptr;
GenerarEnemigo* generarEnemigo = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	registroF = new ParticleForceRegister();
	gravedad = new FuerzaGravedad();
	viento = new WindForce({ 20,0,20 }, { 0,0,0 }, 400);
	registroS = new SolidForceRegister();

	suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(200, 0.1, 200));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1.0 });

	muro1 = gPhysics->createRigidStatic(PxTransform({ 0,5,-200 }));
	PxShape* shape1 = CreateShape(PxBoxGeometry(200, 5, 10));
	muro1->attachShape(*shape1);
	gScene->addActor(*muro1);
	item1 = new RenderItem(shape1, muro1, { 0.1,0.1,0.1,1.0 });

	muro2 = gPhysics->createRigidStatic(PxTransform({ -200,5,0 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(10, 5, 200));
	muro2->attachShape(*shape2);
	gScene->addActor(*muro2);
	item2 = new RenderItem(shape2, muro2, { 0.1,0.1,0.1,1.0 });

	muro3 = gPhysics->createRigidStatic(PxTransform({ 0,5,200 }));
	PxShape* shape3 = CreateShape(PxBoxGeometry(200, 5, 10));
	muro3->attachShape(*shape3);
	gScene->addActor(*muro3);
	item3 = new RenderItem(shape3, muro3, { 0.1,0.1,0.1,1.0 });

	muro4 = gPhysics->createRigidStatic(PxTransform({ 200,5,0 }));
	PxShape* shape4 = CreateShape(PxBoxGeometry(10, 5, 200));
	muro4->attachShape(*shape4);
	gScene->addActor(*muro4);
	item4 = new RenderItem(shape4, muro4, { 0.1,0.1,0.1,1.0 });

	conejoAlien = new ConejoAlien(gScene, gPhysics, { 0,0,0 }, registroS);

	lluvia = new Lluvia({ 0,100,0 }, 1, registroF,1);
	lluvia->setColor({ 0.0,1.0,0.0,1.0 });
	lluvia->addFuerza(gravedad);
	lluvia2 = new Lluvia({ 0,-7,0 }, 100, registroF,0.5);
	lluvia2->setColor({ 0.5,0.5,0.5,1.0 });
	lluvia2->setTam(10.0);
	lluvia2->addFuerza(viento);

	solidSeguirForce = new SolidSeguirForce(5000, conejoAlien);
	float I = (1 / 12) * 0.1 * (pow(5, 2) + pow(5, 2));
	enemigoP1 = new SolidoRigido(gScene, gPhysics, { -180,10,-180 }, 0.1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
	enemigoP1->setName("enemigo");
	enemigoP1->setTiempoVida(1000000);
	enemigoP1->setTensorInercia({ I,I,I });
	enemigoP2 = new SolidoRigido(gScene, gPhysics, { -180,10,180 }, 0.1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
	enemigoP2->setName("enemigo");
	enemigoP2->setTiempoVida(1000000);
	enemigoP2->setTensorInercia({ I,I,I });
	enemigoP3 = new SolidoRigido(gScene, gPhysics, { 180,10,180 }, 0.1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
	enemigoP3->setName("enemigo");
	enemigoP3->setTiempoVida(1000000);
	enemigoP3->setTensorInercia({ I,I,I });
	enemigoP4 = new SolidoRigido(gScene, gPhysics, { 180,10,-180 }, 0.1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
	enemigoP4->setName("enemigo");
	enemigoP4->setTiempoVida(1000000);
	enemigoP4->setTensorInercia({ I,I,I });
	solidFuerzaMuelleFijo1 = new SolidFuerzaMuelleFijo(1000, 100, { -200,10,-200 });
	solidFuerzaMuelleFijo2 = new SolidFuerzaMuelleFijo(1000, 100, { -200,10,200 });
	solidFuerzaMuelleFijo3 = new SolidFuerzaMuelleFijo(1000, 100, { 200,10,200 });
	solidFuerzaMuelleFijo4 = new SolidFuerzaMuelleFijo(1000, 100, { 200,10,-200 });
	registroS->Registrar(solidSeguirForce, enemigoP1);
	registroS->Registrar(solidSeguirForce, enemigoP2);
	registroS->Registrar(solidSeguirForce, enemigoP3);
	registroS->Registrar(solidSeguirForce, enemigoP4);
	registroS->Registrar(solidFuerzaMuelleFijo1, enemigoP1);
	registroS->Registrar(solidFuerzaMuelleFijo2, enemigoP2);
	registroS->Registrar(solidFuerzaMuelleFijo3, enemigoP3);
	registroS->Registrar(solidFuerzaMuelleFijo4, enemigoP4);
	generarEnemigo = new GenerarEnemigo(gScene, gPhysics, { 0,0,0 }, 200, 3, registroS);
	generarEnemigo->addFuerza(solidSeguirForce);
	//SolidoRigido* solidoRigido4 = new SolidoRigido(gScene, gPhysics, { 0,10,-30 }, 1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
	}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	registroF->update(t);
	registroS->update();
	if (lluvia != nullptr) {
		lluvia->update(t);
	}

	if (conejoAlien != nullptr) {
		conejoAlien->update();
	}

	lluvia2->update(t);
	generarEnemigo->update();

	if (enemigoP1 != nullptr) {
		if (enemigoP1->update()) {
			registroS->LiberarSolido(enemigoP1);
			delete enemigoP1;
			enemigoP1 = nullptr;
		}
	}
	if (enemigoP2 != nullptr) {
		if (enemigoP2->update()) {
			registroS->LiberarSolido(enemigoP2);
			delete enemigoP2;
			enemigoP2 = nullptr;
		}
	}
	if (enemigoP3 != nullptr) {
		if (enemigoP3->update()) {
			registroS->LiberarSolido(enemigoP3);
			delete enemigoP3;
			enemigoP3 = nullptr;
		}
	}
	if (enemigoP4 != nullptr) {
		if (enemigoP4->update()) {
			registroS->LiberarSolido(enemigoP4);
			delete enemigoP4;
			enemigoP4 = nullptr;
		}
	}
	
}



// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'T':
	{

		conejoAlien->salto({ 0,0,-1 });
		
		break;
	}
	case 'G':
	{

		conejoAlien->salto({ 0,0,1 });

		break;
	}
	case 'F':
	{

		conejoAlien->salto({ -1,0,0 });
		
		break;
	}
	case 'H':
	{

		conejoAlien->salto({ 1,0,0 });
		
		break;
	}
	case ' ':
	{

		conejoAlien->disparar();
		
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	if (actor1->getName() == "conejo" && actor2->getName() == "enemigo") {
		//cout << "colision conejo enemigo\n";
		conejoAlien->Matar();
	}
	else if (actor1->getName() == "enemigo" && actor2->getName() == "conejo") {
		//cout << "colision enemigo conejo\n";
		conejoAlien->Matar();
	}
	else if (actor1->getName() == "enemigo" && actor2->getName() == "bala") {
		//cout << "colision enemigo bala\n";
		generarEnemigo->destruir(actor1);
		if (enemigoP1 != nullptr) {
			if (actor1 == enemigoP1->getActor()) {
				enemigoP1->Matar();
			}
		}
		if (enemigoP2 != nullptr) {
			if (actor1 == enemigoP2->getActor()) {
				enemigoP2->Matar();
			}
		}
		if (enemigoP3 != nullptr) {
			if (actor1 == enemigoP3->getActor()) {
				enemigoP3->Matar();
			}
		}
		if (enemigoP4 != nullptr) {
			if (actor1 == enemigoP4->getActor()) {
				enemigoP4->Matar();
			}
		}
	}
	else if (actor1->getName() == "bala" && actor2->getName() == "enemigo") {
		//cout << "colision bala enemigo\n";
		generarEnemigo->destruir(actor2);
		if (enemigoP1 != nullptr) {
			if (actor2 == enemigoP1->getActor()) {
				enemigoP1->Matar();
			}
		}
		if (enemigoP2 != nullptr) {
			if (actor2 == enemigoP2->getActor()) {
				enemigoP2->Matar();
			}
		}
		if (enemigoP3 != nullptr) {
			if (actor2 == enemigoP3->getActor()) {
				enemigoP3->Matar();
			}
		}
		if (enemigoP4 != nullptr) {
			if (actor2 == enemigoP4->getActor()) {
				enemigoP4->Matar();
			}
		}
	}
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}