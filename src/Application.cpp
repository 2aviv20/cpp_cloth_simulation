#include "Application.h"
#include "./Physics/Constants.h"
#include "./Physics/Cloth.h"
#include <iostream>

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();
    mouse = new Mouse();


    int clothSpacing = 15;
    int clothWidth = 300/clothSpacing;
    int clothHeight = 300/clothSpacing;

    int startX = Graphics::Width() * 0.5f - clothWidth * clothSpacing * 0.5f;
    int startY = Graphics::Height() * 0.1f;

    cloth = new Cloth(clothWidth, clothHeight, clothSpacing, startX, startY);
    timePreviousFrame = SDL_GetTicks();

    // A === B
    // *     *
    // *     *
    // *     *
    // C === D
    ParticleVarlet* pA = new ParticleVarlet(220, 20, 10.0f);
    //ParticleVarlet* pB = new ParticleVarlet(320, 20, 10.0f);
    //ParticleVarlet* pC = new ParticleVarlet(220, 120, 10.0f);
    //ParticleVarlet* pD = new ParticleVarlet(320, 120, 10.0f);
    //Stick* sAB = new Stick(pA, pB, 100);
    //Stick* sCD = new Stick(pC, pD, 100);
    //Stick* sAC = new Stick(pA, pC, 100);
    //Stick* sBD = new Stick(pB, pD, 100);
    //Stick* sCB = new Stick(pC, pB, 100);
    //Stick* sAD = new Stick(pA, pD, 100);
    particleVarlet.push_back(pA);
    //particleVarlet.push_back(pB);
    //particleVarlet.push_back(pC);
    //particleVarlet.push_back(pD);
    //sticks.push_back(sAB);
    //sticks.push_back(sCD);
    //sticks.push_back(sAC);
    //sticks.push_back(sBD);
    //sticks.push_back(sCB);
    //sticks.push_back(sAD);

}

void Application::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
            break;
        case SDL_MOUSEMOTION:
        {
            int x = event.motion.x;
            int y = event.motion.y;
            mouse->UpdatePosition(x, y);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            mouse->UpdatePosition(x, y);

            if (!mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT)
            {
                mouse->SetLeftMouseButton(true);
            }
            if (!mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse->SetRightMouseButton(true);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT)
            {
                mouse->SetLeftMouseButton(false);
            }
            if (mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse->SetRightMouseButton(false);
            }
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
            {
                mouse->IncreaseCursorSize(10);
            }
            else if (event.wheel.y < 0)
            {
                mouse->IncreaseCursorSize(-10);
            }
            break;
        }
    }
}



void Application::Update() {
    // Wait some time until the reach the target frame time in milliseconds
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);
    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016)
        deltaTime = 0.016;
    // Set the time of the current frame to be used in the next one
    timePreviousFrame = SDL_GetTicks();

    //invoke all updates 
    cloth->Update(mouse,deltaTime);
}


void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    //for (auto particle: particleVarlet) {
    //    particle->Draw();
    //}
    //for (auto stick : sticks) {
    //    stick->Draw();
    //}
    
    cloth->Draw();

    Graphics::RenderFrame();
}

void Application::Destroy() {
    //for (auto particle: particleVarlet) {
    //    delete particle;
    //}
    //for (auto stick : sticks) {
    //    delete stick;
    //}
    delete cloth;
    Graphics::CloseWindow();
}
