#ifndef PARTICLE_VARLET_H
#define PARTICLE_VARLET_H
#include "../Graphics.h"
#include "Vec2.h"
#include "../Mouse.h"
#include "Stick.h"
#include <iostream>

//class Stick;
class ParticleVarlet {
public:
	Vec2 position;
	Vec2 prevPosition;
	Vec2 initPosition;
	float mass;
	Stick* sticks[2];
	bool isPinned = false;
	bool isSelected = false;

	ParticleVarlet(int x, int y, float mass);
	void varlet(float deltaTime);
	void Update(float deltaTime, float drag, Vec2& gravity, float elasticity, Mouse* mouse, int width, int height);
	void Draw();
	void keepInsideView();
	void Pin();
	void AddStick(Stick* stick, int index);
	void SetPosition(int x, int y);
};
#endif
