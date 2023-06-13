#include "Cloth.h"
#include "Particle_varlet.h"
#include "Stick.h"
#include "../Mouse.h"
Cloth::Cloth(int width, int height, float spacing, int startX, int startY)
{
	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++)
		{
			ParticleVarlet* point = new ParticleVarlet(startX + x * spacing, startY + y * spacing, this->pointMass);

			if (x != 0)
			{
				ParticleVarlet* leftPoint = points[this->points.size() - 1];
				Stick* s = new Stick(point, leftPoint, spacing);
				leftPoint->AddStick(s, 0);
				point->AddStick(s, 0);
				this->sticks.push_back(s);
			}

			if (y != 0)
			{
				ParticleVarlet* upPoint = points[x + (y - 1) * (width + 1)];
				Stick* s = new Stick(point, upPoint, spacing);
				upPoint->AddStick(s, 1);
				point->AddStick(s, 1);
				this->sticks.push_back(s);
			}

			if (y == 0 && x % 2 == 0)
			{
				point->Pin();
			}

			this->points.push_back(point);
		}
	}
	std::cout << "init is done \n";
}

void Cloth::Update(Mouse* mouse, float deltaTime)
{
	for (int i = 0; i < points.size(); i++)
	{
		ParticleVarlet* p = points[i];
		p->Update(deltaTime, drag, gravity, elasticity, mouse, Graphics::Width(), Graphics::Height());
	};

	for (int i = 0; i < sticks.size(); i++)
	{
		sticks[i]->Update();
	};
}

void Cloth::Draw() const
{
	for (auto stick : sticks) {
		stick->Draw();
	}
}

Cloth::~Cloth()
{
	for (auto point : points)
	{
		delete point;
	}

	for (auto stick : sticks)
	{
		delete stick;
	}
}