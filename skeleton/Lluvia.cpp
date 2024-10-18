#include "Lluvia.h"

Lluvia::Lluvia(Vector3 fuente, float radio)
	:ParticleGenerator(fuente, 1000), radio(radio)
{}

void Lluvia::update(double t) {
	generateRandom();

	Particle* particula = new Particle({fx,fuente.y,fz}, {x,y,z},{0,0,0},1,0.3);
	particula->setColor({ 0,0,1,1 });
	//particula->setTiempoVida(tv);
	lista.push_back(particula);

	for (auto it = lista.begin(); it != lista.end();) {
		bool dead = (*it)->integrate(t);
		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango) {
			delete(*it);
			it = lista.erase(it);
		}
		else {
			it++;
		}
	}
}

void Lluvia::generateRandom() {
	x = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	y = -50;
	z = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	fx = normal_distribution<float>(fuente.x-radio, fuente.x+radio)(randomGenerator);
	fz = normal_distribution<float>(fuente.z-radio, fuente.z+radio)(randomGenerator);
	//tv = uniform_real_distribution<float>(1000, 5000)(randomGenerator);
}