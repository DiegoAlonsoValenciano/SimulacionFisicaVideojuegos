#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 fuente, int rango) 
	:fuente(fuente), rango(rango)
{}

ParticleGenerator::~ParticleGenerator() {
	for (auto it = lista.begin(); it != lista.end();) {
		delete(*it);
		it = lista.erase(it);
	}
}

//void ParticleGenerator::update(double t) {
//	
//	generateRandom();
//
//	lista.push_back(new Particle(fuente, {x,y,z}));
//
//	for (auto it = lista.begin(); it != lista.end();) {
//		/*float r = uniform_real_distribution<float>(0, 1)(randomGenerator);
//		float g = uniform_real_distribution<float>(0, 1)(randomGenerator);
//		float b = uniform_real_distribution<float>(0, 1)(randomGenerator);
//		(*it)->setColor({ r,g,b,1 });*/
//		bool dead = (*it)->integrate(t);
//		if (dead || ((*it)->GetPos() - fuente).magnitude() > rango) {
//			delete(*it);
//			it = lista.erase(it);
//		}
//		else {
//			it++;
//		}
//	}
//}

//void ParticleGenerator::generateRandom() {
//	x = uniform_real_distribution<float>(-10, 10)(randomGenerator);
//	y = uniform_real_distribution<float>(-10, 10)(randomGenerator);
//	z = uniform_real_distribution<float>(-10, 10)(randomGenerator);
//}
