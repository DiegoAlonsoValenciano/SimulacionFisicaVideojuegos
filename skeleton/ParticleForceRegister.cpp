#include "ParticleForceRegister.h"

ParticleForceRegister::ParticleForceRegister() {

}

void ParticleForceRegister::Registrar(ForceGenerator* f, Particle* p) {
	fuerzas.insert({ f,p });
}

void ParticleForceRegister::LiberarFuerza(ForceGenerator* f) {
	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		if ((*it).first == f) {
			it = fuerzas.erase(it);
		}
	}
}

void ParticleForceRegister::LiberarParticula(Particle* p) {
	for (auto it = fuerzas.begin(); it != fuerzas.end();) {
		if ((*it).second == p) {
			it = fuerzas.erase(it);
		}
		else {
			it++;
		}
	}
}

void ParticleForceRegister::update() {
	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		(*it).first->update((*it).second);
	}
}
