#include "MuchasParticulas.h"

MuchasParticulas::MuchasParticulas(Vector3 fuente, float radio, ParticleForceRegister* r)
	:ParticleGenerator(fuente, radio, r)
{
	for (int i = 0; i < 500; i++) {
		generateRandom();

		Particle* particula = new Particle({x,y,z}, {0,0,0}, 5, {0,0,0}, 1, 0.5);
		particula->setTiempoVida(tv);
		particula->setEuler(false);
		lista.push_back(particula);
	}
}

void MuchasParticulas::update(double t) {

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

void MuchasParticulas::generateRandom() {
	x = uniform_real_distribution<float>(fuente.x-5, fuente.x+5)(randomGenerator);
	y = uniform_real_distribution<float>(fuente.y-5, fuente.y+5)(randomGenerator);
	z = uniform_real_distribution<float>(fuente.z-5, fuente.z+5)(randomGenerator);
	tv = 10000;
}
