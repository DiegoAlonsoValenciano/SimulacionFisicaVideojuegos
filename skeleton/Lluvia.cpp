#include "Lluvia.h"

Lluvia::Lluvia(Vector3 fuente, float radio, ParticleForceRegister* r, float m)
	:ParticleGenerator(fuente, 1000, r), radio(radio), masa(m)
{
	color = Vector4(0, 0, 1, 1);
	tam = 0.3;
}

void Lluvia::update(double t) {
	generateRandom();

	Particle* particula = new Particle({fx,fuente.y,fz}, {x,y,z}, masa,{0,0,0},1,tam);
	particula->setColor(color);
	particula->setEuler(false);
	particula->setTiempoVida(tv);
	lista.push_back(particula);

	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		registro->Registrar((*it), particula);
	}

	for (auto it = lista.begin(); it != lista.end();) {
		bool dead = (*it)->integrate(t);
		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango/2 || (*it)->GetPos().y < -10) {
			registro->LiberarParticula((*it));
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
	y = 0;
	z = uniform_real_distribution<float>(-1, 1)(randomGenerator);
	fx = normal_distribution<float>(fuente.x-radio, fuente.x+radio)(randomGenerator);
	fz = normal_distribution<float>(fuente.z-radio, fuente.z+radio)(randomGenerator);
	tv = uniform_real_distribution<float>(1000, 5000)(randomGenerator);
}