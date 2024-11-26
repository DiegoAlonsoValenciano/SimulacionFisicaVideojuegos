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

Proyectil* proyectil = nullptr;
Lluvia* lluvia = nullptr;
Niebla* niebla = nullptr;
Party* party = nullptr;
ParticleForceRegister* registroF = nullptr;
FuerzaGravedad* gravedad = nullptr;
WindForce* viento = nullptr;
FuerzaTorbellino* torbellino = nullptr;
FuerzaExplosion* explosion = nullptr;
MuchasParticulas* muchasParticulas = nullptr;
FuerzaMuelle* fuerzaMuelle1 = nullptr;
FuerzaMuelle* fuerzaMuelle2 = nullptr;
FuerzaMuelleFijo* fuerzaMuelleFijo = nullptr;
FuerzaFlotacion* fuerzaFlotacion = nullptr;
FuerzaGomaElastica* fuerzaGomaElastica1 = nullptr;
FuerzaGomaElastica* fuerzaGomaElastica2 = nullptr;

Particle* p1 = nullptr;
Particle* p2 = nullptr;
Particle* p3 = nullptr;
Particle* p4 = nullptr;
Particle* p5 = nullptr;
Particle* p6 = nullptr;
Particle* p7 = nullptr;
Particle* p8 = nullptr;

SolidParty* solidParty;

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
	viento = new WindForce({ 20,0,20 },{0,0,0},100);
	torbellino = new FuerzaTorbellino({ 0,0,0 }, 100);
	explosion = new FuerzaExplosion({ 0,15,0 }, 50);

	p1 = new Particle({ 30,0,20 }, { 0,0,10 }, 2);
	p2 = new Particle({ -30,0,20 }, { 0,0,-10 }, 2);
	p1->setEuler(false);
	p2->setEuler(false);
	p1->setColor({ 0.0,1.0,0.0,1.0 });
	p2->setColor({ 0.0,1.0,0.0,1.0 });
	fuerzaMuelle1 = new FuerzaMuelle(10, 10, p1);
	fuerzaMuelle2 = new FuerzaMuelle(10, 10, p2);
	registroF->Registrar(fuerzaMuelle1, p2);
	registroF->Registrar(fuerzaMuelle2, p1);

	p3 = new Particle({ 0,20,30 }, { 10,0,0 }, 2);
	p3->setEuler(false);
	fuerzaMuelleFijo = new FuerzaMuelleFijo(10, 10, { 0,0,0 });
	registroF->Registrar(fuerzaMuelleFijo, p3);
	//registroF->Registrar(gravedad, p3);

	fuerzaFlotacion = new FuerzaFlotacion(10, 10, 1, {0,0,30});
	p4 = new Particle({ 0,20,30 }, { 0,0,0 }, 5);
	p5 = new Particle({ 30,20,30 }, { 0,0,0 }, 1);
	p6 = new Particle({ -30,20,30 }, { 0,0,0 }, 10);
	p4->setEuler(false);
	p5->setEuler(false);
	p6->setEuler(false);
	p4->setColor({ 0.0,0.0,1.0,1.0 });
	p5->setColor({ 0.0,0.0,1.0,1.0 });
	p6->setColor({ 0.0,0.0,1.0,1.0 });
	registroF->Registrar(fuerzaFlotacion, p4);
	registroF->Registrar(fuerzaFlotacion, p5);
	registroF->Registrar(fuerzaFlotacion, p6);
	registroF->Registrar(gravedad, p4);
	registroF->Registrar(gravedad, p5);
	registroF->Registrar(gravedad, p6);

	p7 = new Particle({ 30,20,20 }, { 0,0,10 }, 2);
	p8 = new Particle({ -30,20,20 }, { 0,0,-10 }, 2);
	p7->setEuler(false);
	p8->setEuler(false);
	p7->setColor({ 1.0,1.0,0.0,1.0 });
	p8->setColor({ 1.0,1.0,0.0,1.0 });
	fuerzaGomaElastica1 = new FuerzaGomaElastica(10, 10, p7);
	fuerzaGomaElastica2 = new FuerzaGomaElastica(10, 10, p8);
	registroF->Registrar(fuerzaGomaElastica1, p8);
	registroF->Registrar(fuerzaGomaElastica2, p7);

	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	RenderItem* item;
	item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1.0 });

	SolidoRigido* solidoRigido = new SolidoRigido(gScene, gPhysics, { -70,300,-70 }, 0.5,{0,5,0},{0,0,0},{5,5,5});
	SolidoRigido* solidoRigido2 = new SolidoRigido(gScene, gPhysics, { -70,100,-70 }, 0.05, { 0,5,0 }, { 0,0,0 }, { 5,5,5 });
	solidoRigido2->setColor({ 0.0,1.0,0.0,1.0 });
	SolidoRigido* solidoRigido3 = new SolidoRigido(gScene, gPhysics, { -70,200,-70 }, 0.15, { 0,5,0 }, { 0,0,0 }, { 5,5,5 });
	solidoRigido3->setColor({ 0.0,0.0,1.0,1.0 });


	solidParty = new SolidParty(gScene,gPhysics,{-50,40,-50},100,20);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	if (proyectil != nullptr) {
		proyectil->integrate(t);
		if (proyectil->GetPos().y < 0) {
			delete proyectil;
			proyectil = nullptr;
		}
	}
	registroF->update(t);
	if (lluvia != nullptr) {
		lluvia->update(t);
	}
	if (niebla != nullptr) {
		niebla->update(t);
	}
	if (party != nullptr) {
		party->update(t);
	}
	if (muchasParticulas != nullptr) {
		muchasParticulas->update(t);
	}
	p1->integrate(t);
	p2->integrate(t);
	p3->integrate(t);
	p4->integrate(t);
	p5->integrate(t);
	p6->integrate(t);
	p7->integrate(t);
	p8->integrate(t);

	solidParty->update();
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	
	if (proyectil != nullptr) {
		delete proyectil;
		proyectil = nullptr;
	}
	if (lluvia != nullptr) {
		delete lluvia;
		lluvia = nullptr;
	}
	if (niebla != nullptr) {
		delete niebla;
		niebla = nullptr;
	}
	if (party != nullptr) {
		delete party;
		party = nullptr;
	}
	if (muchasParticulas != nullptr) {
		delete muchasParticulas;
		muchasParticulas = nullptr;
	}

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
	case 'B': {
		if (proyectil == nullptr) {
			proyectil = new Proyectil(camera.p, {-10,0,-10}, 10);
		}
		break;
	}
	case 'L': {
		if (lluvia == nullptr) {
			lluvia = new Lluvia({ 0,100,0 }, 10,registroF);
			lluvia->addFuerza(gravedad);
			lluvia->addFuerza(torbellino);
		}
		if (niebla != nullptr) {
			delete niebla;
			niebla = nullptr;
		}
		if (party != nullptr) {
			delete party;
			party = nullptr;
		}
		if (muchasParticulas != nullptr) {
			delete muchasParticulas;
			muchasParticulas = nullptr;
		}
		break;
	}
	case 'N': {
		if (niebla == nullptr) {
			niebla = new Niebla({ 0,50,0 }, 10,registroF);
			niebla->addFuerza(torbellino);
		}
		if (lluvia != nullptr) {
			delete lluvia;
			lluvia = nullptr;
		}
		if (party != nullptr) {
			delete party;
			party = nullptr;
		}
		if (muchasParticulas != nullptr) {
			delete muchasParticulas;
			muchasParticulas = nullptr;
		}
		break;
	}
	case 'P': {
		if (party == nullptr) {
			party = new Party({ 0,0,0 }, 100,registroF);
		}
		if (lluvia != nullptr) {
			delete lluvia;
			lluvia = nullptr;
		}
		if (niebla != nullptr) {
			delete niebla;
			niebla = nullptr;
		}
		if (muchasParticulas != nullptr) {
			delete muchasParticulas;
			muchasParticulas = nullptr;
		}
		break;
	}
	case 'E': {
		if (muchasParticulas == nullptr) {
			explosion = new FuerzaExplosion({ 0,15,0 }, 50);
			muchasParticulas = new MuchasParticulas({ 0,15,0 }, 100, registroF);
			muchasParticulas->addFuerza(explosion);
		}
		if (lluvia != nullptr) {
			delete lluvia;
			lluvia = nullptr;
		}
		if (niebla != nullptr) {
			delete niebla;
			niebla = nullptr;
		}
		if (party != nullptr) {
			delete party;
			party = nullptr;
		}
		break;
	}
	case 'K': {
		double kaux;
		cin >> kaux;

		fuerzaMuelleFijo->setK(kaux);

		break;
	}
	case ' ':
	{
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