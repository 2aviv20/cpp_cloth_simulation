#ifndef CLOTH_H
#define CLOTH_H


#include <vector>
#include "Particle_varlet.h"
#include "Stick.h"
#include "../Graphics.h"
#include "../Mouse.h"

class Cloth
{
public:
	Vec2 gravity = { 0.0f, 981.0f };
	float drag = 0.01f;
	float elasticity = 10.0f;
	float pointMass = 10.0f;
	std::vector<ParticleVarlet*> points;
	std::vector<Stick*> sticks;
	Cloth() = default;
	Cloth(int width, int height, float spacing, int startX, int startY);
	~Cloth();
	void Update(Mouse* mouse, float deltaTime);
	void Draw() const;
};

#endif