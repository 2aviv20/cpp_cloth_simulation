#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Physics/Particle.h"
#include "./Physics/Particle_varlet.h"
#include "./Physics/Stick.h"
#include "./Physics/Cloth.h"
#include "./Mouse.h"
#include <vector>

class Application {
    private:
        bool running = false;
        std::vector<Particle*> particles;
        std::vector<ParticleVarlet*> particleVarlet;
        std::vector<Stick*> sticks;
        Cloth* cloth;
        Vec2 pushForce = Vec2(0, 0);
        int timePreviousFrame;
        Mouse* mouse = nullptr;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
};

#endif
