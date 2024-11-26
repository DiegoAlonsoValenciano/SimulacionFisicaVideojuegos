#include "GeneradorSolidoRigido.h"

GeneradorSolidoRigido::GeneradorSolidoRigido(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite)
	:gScene(gScene), gPhysics(gPhysics), fuente(fuente), rango(rango), limite(limite)
{}

GeneradorSolidoRigido::~GeneradorSolidoRigido() {
	for (auto it = lista.begin(); it != lista.end();) {
		delete(*it);
		it = lista.erase(it);
	}
}
