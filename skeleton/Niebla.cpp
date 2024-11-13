#include "Niebla.h"

Niebla::Niebla(Vector3 fuente, float radio, ParticleForceRegister* r)
	:ParticleGenerator(fuente, 1000, r), radio(radio)
{}

void Niebla::update(double t) {
	generateRandom();

	Particle* particula = new Particle({ fx,fy,fz }, { x,y,z }, 1, { 0,0,0 }, 1, 0.1);
	particula->setColor({ 0.7,0.7,0.7,1 });
	particula->setTiempoVida(tv);
	particula->setEuler(false);
	lista.push_back(particula);

	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		registro->Registrar((*it), particula);
	}

	for (auto it = lista.begin(); it != lista.end();) {
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

void Niebla::generateRandom() {
	x = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	y = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	z = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	fx = normal_distribution<float>(fuente.x - radio, fuente.x + radio)(randomGenerator);
	fy = normal_distribution<float>(fuente.x - radio, fuente.x + radio)(randomGenerator);
	fz = normal_distribution<float>(fuente.z - radio, fuente.z + radio)(randomGenerator);
	tv = uniform_real_distribution<float>(100, 5000)(randomGenerator);
}
