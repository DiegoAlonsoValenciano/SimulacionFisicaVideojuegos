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
	if (lluvia != nullptr) {
		lluvia->update(t);
	}
	if (niebla != nullptr) {
		niebla->update(t);
	}
	if (party != nullptr) {
		party->update(t);
	}
	registroF->update();
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
	case 'N': {
		if (niebla == nullptr) {
			niebla = new Niebla({ 0,50,0 }, 10,registroF);
		}
		if (lluvia != nullptr) {
			delete lluvia;
			lluvia = nullptr;
		}
		if (party != nullptr) {
			delete party;
			party = nullptr;
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