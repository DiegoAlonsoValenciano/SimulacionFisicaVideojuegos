#include "SolidParty.h"

SolidParty::SolidParty(PxScene* gScene, PxPhysics* gPhysics, Vector3 fuente, int rango, int limite)
	:GeneradorSolidoRigido(gScene,gPhysics,fuente,rango,limite)
{}

void SolidParty::update() {
	generateRandom();

	if (lista.size() <= limite) {
		SolidoRigido* solidoRigido = new SolidoRigido(gScene, gPhysics, {x,y,z}, 1, {xl,yl,zl}, {xa,ya,za}, {2,2,2});
		solidoRigido->setTiempoVida(tv);
		lista.push_back(solidoRigido);
	}
	

	for (auto it = lista.begin(); it != lista.end();) {
		generateRandom();
		(*it)->setColor({ r,g,b,1 });
		bool dead = (*it)->update();
		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango) {
			delete(*it);
			it = lista.erase(it);
		}
		else {
			it++;
		}
	}
}

void SolidParty::generateRandom() {
	x = uniform_real_distribution<float>(fuente.x-30, fuente.x+30)(randomGenerator);
	y = uniform_real_distribution<float>(fuente.y -30, fuente.y+30)(randomGenerator);
	z = uniform_real_distribution<float>(fuente.z -30, fuente.z+30)(randomGenerator);
	xl = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	yl = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	zl = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	xa = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	ya = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	za = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	r = uniform_real_distribution<float>(0, 1)(randomGenerator);
	g = uniform_real_distribution<float>(0, 1)(randomGenerator);
	b = uniform_real_distribution<float>(0, 1)(randomGenerator);
	tv = uniform_real_distribution<float>(100, 5000)(randomGenerator);
}
