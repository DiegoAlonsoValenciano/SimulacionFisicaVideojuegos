#include "SolidForceRegister.h"

SolidForceRegister::SolidForceRegister() {

}

void SolidForceRegister::Registrar(SolidForceGenerator* f, SolidoRigido* s) {
	fuerzas.insert({ f,s });
}

void SolidForceRegister::LiberarFuerza(SolidForceGenerator* f) {
	for (auto it = fuerzas.begin(); it != fuerzas.end();) {
		if ((*it).first == f) {
			it = fuerzas.erase(it);
		}
		else {
			it++;
		}
	}
}

void SolidForceRegister::LiberarSolido(SolidoRigido* s) {
	for (auto it = fuerzas.begin(); it != fuerzas.end();) {
		if ((*it).second == s) {
			it = fuerzas.erase(it);
		}
		else {
			it++;
		}
	}
}

void SolidForceRegister::update() {
	for (auto it = fuerzas.begin(); it != fuerzas.end(); it++) {
		(*it).first->update((*it).second);
	}
}
