#include "GenerarBala.h"

GenerarBala::GenerarBala(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite, SolidForceRegister* r)
	:GeneradorSolidoRigido(gScene, gPhysics, fuente, rango, limite, r)
{
	tv = 500;
}

void GenerarBala::update() {

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

void GenerarBala::disparo(Vector3 pos, Vector3 dir) {
	if (lista.size() <= limite) {
		SolidoRigido* solidoRigido = new SolidoRigido(gScene, gPhysics, pos, 0.1, dir*vel, { 0,0,0 }, 3);
		solidoRigido->setTiempoVida(tv);
		solidoRigido->setColor({ 0.0,0.0,1.0,1.0 });
		solidoRigido->setName("bala");
		float I = (2 / 5) * 0.1 * pow(3, 2);
		solidoRigido->setTensorInercia(Vector3(I, I, I));
		lista.push_back(solidoRigido);
		for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
			registro->Registrar((*it), solidoRigido);
		}
	}
}

void GenerarBala::generateRandom() {
	
}
