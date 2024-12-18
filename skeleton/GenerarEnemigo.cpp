#include "GenerarEnemigo.h"

GenerarEnemigo::GenerarEnemigo(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r)
	:GeneradorSolidoRigido(gScene, gPhysics, fuente, rango, limite, r)
{}

void GenerarEnemigo::update() {

	if (lista.size() <= limite) {
		generateRandom();
		SolidoRigido* solidoRigido = new SolidoRigido(gScene, gPhysics, { x,0,z }, 0.1, { 0,0,0 }, { 0,0,0 }, { 5,5,5 });
		solidoRigido->setTiempoVida(tv);
		solidoRigido->setName("enemigo");
		float I = (1 / 12) * 0.1 * (pow(5, 2) + pow(5, 2));
		solidoRigido->setTensorInercia(Vector3(I,I,I));
		lista.push_back(solidoRigido);
		for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
			registro->Registrar((*it), solidoRigido);
		}
	}


	for (auto it = lista.begin(); it != lista.end();) {
		bool dead = (*it)->update();
		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango) {
			registro->LiberarSolido((*it));
			delete(*it);
			it = lista.erase(it);
		}
		else {
			it++;
		}
	}
}

void GenerarEnemigo::generateRandom() {
	x = uniform_real_distribution<float>(fuente.x - rango, fuente.x + rango)(randomGenerator);
	z = uniform_real_distribution<float>(fuente.z - rango, fuente.z + rango)(randomGenerator);
	tv = uniform_real_distribution<float>(10000, 20000)(randomGenerator);
}

