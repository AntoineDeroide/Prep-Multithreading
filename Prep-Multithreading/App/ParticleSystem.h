#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <set>

class Particle;

class ParticleSystem
{
public:
	static ParticleSystem& Instance();

	ParticleSystem();
	~ParticleSystem();

private:
	std::set<Particle*> m_particles;

};

#endif // PARTICLESYSTEM_H