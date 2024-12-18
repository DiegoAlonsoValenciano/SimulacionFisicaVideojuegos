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
	for (auto it = lista.begin(); it != lista.end();it++) {
		registro->Registrar(f, (*it));
	}
}

void ParticleGenerator::quitarFuerza(ForceGenerator* f) {
	for (auto it = fuerzas.begin(); it != fuerzas.end();) {
		if ((*it) == f) {
			it = fuerzas.erase(it);
		}
		else {
			it++;
		}
	}
}

void ParticleGenerator::setColor(Vector4 c) {
	color = c;
}


void ParticleGenerator::setTam(float t) {
	tam = t;
}
