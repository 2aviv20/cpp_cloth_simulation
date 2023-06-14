#include "Particle_varlet.h"
ParticleVarlet::ParticleVarlet(int x, int y, float mass)
{
    
    this->position = Vec2(x, y);
    this->prevPosition = Vec2(x, y);
	this->initPosition = Vec2(x, y);
    this->mass = mass;
}

void ParticleVarlet::Update(float deltaTime, float drag, Vec2& acceleration, float elasticity, Mouse* mouse, int width, int height) {
	Vec2 cursorToPosDir = position - mouse->GetPosition();
	float cursorToPosDist = cursorToPosDir.x * cursorToPosDir.x + cursorToPosDir.y * cursorToPosDir.y;
	float cursorSize = mouse->GetCursorSize();
	isSelected = cursorToPosDist < cursorSize* cursorSize;

	for (Stick* stick : sticks)
	{
		if (stick != nullptr)
			stick->SetIsSelected(isSelected);
	}

	if (mouse->GetLeftButtonDown() && isSelected)
	{
		Vec2 difference = mouse->GetPosition() - mouse->GetPreviousPosition();

		if (difference.x > elasticity) difference.x = elasticity;
		if (difference.y > elasticity) difference.y = elasticity;
		if (difference.x < -elasticity) difference.x = -elasticity;
		if (difference.y < -elasticity) difference.y = -elasticity;

		prevPosition = position - difference;
	}

	if (mouse->GetRightMouseButton() && isSelected)
	{
		for (Stick* stick : sticks)
		{
			if (stick != nullptr)
				stick->Break();
		}
	}

	if (isPinned) {
		position = initPosition;
		return;
	}

	// Inertia: objects in motion stay in motion. 



	//Vec2 newPos = (position + (position - prevPosition)) + (acceleration * deltaTime * deltaTime) ;
	Vec2 newPos = position + (position - prevPosition) * (1.0f - drag) + acceleration * (1.0f - drag) * deltaTime * deltaTime;
	prevPosition = position;
	position = newPos;

	this->keepInsideView();
}

void ParticleVarlet::Draw() {
    Graphics::DrawFillCircle(this->position.x, this->position.y, this->mass, 0xFFFFFFFF);
}

void ParticleVarlet::varlet(float deltaTime)
{

	Vec2 force = Vec2(300.0, 981.0f);
	Vec2 acceleration = force / this->mass;
	Vec2 prev = Vec2(this->position.x, this->position.y);//temp var

	// keepInsideView
	int width = Graphics::windowWidth;
	int height = Graphics::windowHeight;
	if (this->position.y >= height) { 
		this->position.y = height;
		acceleration.y = height * -2; 
	}
	if (this->position.x >= width) { 
		this->position.x = width;
		acceleration.x = width * -2;
	}
	if (this->position.y < 0) this->position.y = 0; acceleration.y * -1;
	if (this->position.x < 0) this->position.x = 0; acceleration.x * -1;


    float x = (2 * this->position.x - this->prevPosition.x + acceleration.x * (deltaTime * deltaTime));
    float y = (2 * this->position.y - this->prevPosition.y + acceleration.y * (deltaTime * deltaTime));
    this->position = Vec2(x, y);
    this->prevPosition = Vec2(prev.x,prev.y);
    
}

void ParticleVarlet::keepInsideView() {
    int width  = Graphics::windowWidth;
    int height = Graphics::windowHeight;
    if (this->position.y >= height) this->position.y = height;
    if (this->position.x >= width) this->position.x = width;
    if (this->position.y < 0) this->position.y = 0;
    if (this->position.x < 0) this->position.x = 0;
}

void ParticleVarlet::Pin()
{
    this->isPinned = true;
}

void ParticleVarlet::AddStick(Stick* stick , int index)
{
    this->sticks[index] = stick;
}

void ParticleVarlet::SetPosition(int x, int y) {
    this->position = Vec2(x, y);
}



