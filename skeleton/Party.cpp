#include "Party.h"

Party::Party(Vector3 fuente, float radio, ParticleForceRegister* r)
	:ParticleGenerator(fuente, radio, r)
{

}

void Party::update(double t) {
	generateRandom();

	Particle* particula = new Particle(fuente, { x,y,z },100000);
	particula->setTiempoVida(tv);
	lista.push_back(particula);

	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		registro->Registrar((*it), particula);
	}

	for (auto it = lista.begin(); it != lista.end();) {
		generateRandom();
		(*it)->setColor({ r,g,b,1 });
		bool dead = (*it)->integrate(t);
		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango) {
			registro->LiberarParticula((*it));
			delete(*it);
			it = lista.erase(it);
		}
		else {
			it++;
		}
	}
}

void Party::generateRandom() {
	x = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	y = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	z = uniform_real_distribution<float>(-10, 10)(randomGenerator);
	r = uniform_real_distribution<float>(0, 1)(randomGenerator);
	g = uniform_real_distribution<float>(0, 1)(randomGenerator);
	b = uniform_real_distribution<float>(0, 1)(randomGenerator);
	tv = uniform_real_distribution<float>(100, 5000)(randomGenerator);
}
