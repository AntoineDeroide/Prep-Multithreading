#include "Particle.h"

Particle::Particle(float _x, float _y, float _z, float _size) : 
    m_center(_x, _y, _z), 
    m_size(_size)
{
    //code...
}

void Particle::Move(float _x, float _y, float _z)
{
    m_center.x += _x;
    m_center.y += _y;
    m_center.z += _z;
}