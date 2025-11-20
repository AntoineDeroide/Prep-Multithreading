#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vertex.h"

class Particle
{
public:
	Particle();
	Particle(float _x, float _y, float _z, float _size = 5);
	~Particle() = default;

	void Move(float _x, float _y, float _z);

private:
	Vertex m_center;
	unsigned int m_size;

};


#endif // PARTICLE_H