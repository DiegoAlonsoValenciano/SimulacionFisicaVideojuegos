#include "GeneradorSolidoRigido.h"

GeneradorSolidoRigido::GeneradorSolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r)
	:gScene(gScene), gPhysics(gPhysics), fuente(fuente), rango(rango), limite(limite), registro(r)
{}

GeneradorSolidoRigido::~GeneradorSolidoRigido() {
	for (auto it = lista.begin(); it != lista.end();) {
		delete(*it);
		it = lista.erase(it);
	}
}

void GeneradorSolidoRigido::addFuerza(SolidForceGenerator* f) {
	fuerzas.push_back(f);
	for (auto it = lista.begin(); it != lista.end(); it++) {
		registro->Registrar(f, (*it));
	}
}

void GeneradorSolidoRigido::quitarFuerza(SolidForceGenerator* f) {
	for (auto it = fuerzas.begin(); it != fuerzas.end();) {
		if ((*it) == f) {
			it = fuerzas.erase(it);
		}
		else {
			it++;
		}
	}
}

void GeneradorSolidoRigido::destruir(physx::PxActor* actor) {
	for (auto it = lista.begin(); it != lista.end(); it++) {
		if ((*it)->getActor() == actor) {
			(*it)->Matar();
		}
	}
}
