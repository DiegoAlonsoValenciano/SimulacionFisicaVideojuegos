#include "MuchasParticulas.h"

MuchasParticulas::MuchasParticulas(Vector3 fuente, float radio, ParticleForceRegister* r)
	:ParticleGenerator(fuente, radio, r)
{
	for (int i = 0; i < 500; i++) {
		generateRandom();

		Particle* particula = new Particle(fuente, { x,y,z }, 5,{0,0,0},1,0.5);
		particula->setTiempoVida(tv);
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
	x = uniform_real_distribution<float>(fuente.x-10, fuente.x+10)(randomGenerator);
	y = uniform_real_distribution<float>(fuente.y-10, fuente.y+10)(randomGenerator);
	z = uniform_real_distribution<float>(fuente.z-10, fuente.z+10)(randomGenerator);
	tv = 10000;
}
