#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 fuente, int rango, ParticleForceRegister* r)
	:fuente(fuente), rango(rango), registro(r)
{}

ParticleGenerator::~ParticleGenerator() {
	for (auto it = lista.begin(); it != lista.end();) {
		registro->LiberarParticula((*it));
		delete(*it);
		it = lista.erase(it);
	}
}

void ParticleGenerator::addFuerza(ForceGenerator* f) {
	fuerzas.push_back(f);
}
