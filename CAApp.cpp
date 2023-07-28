#include <iostream>
#include "CAApp.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int CAApp::OnExecute()
{
    if ( !OnInit() )
    {
        return -1;
    }

    SDL_Event evt;

    while (_running)
    {
        while (SDL_PollEvent(&evt))
        {
            OnEvent(&evt);
        }

        OnLoop();
        OnRender();

        SDL_Delay(16);
    }

    OnCleanup();

    return 0u;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool CAApp::OnInit()
{
    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    _window = SDL_CreateWindow( "Cell Life",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 windowFlags );

    if ( !_window )
    {
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    _renderer = SDL_CreateRenderer(_window, -1, rendererFlags);
    if ( !_renderer )
    {
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void CAApp::OnEvent(SDL_Event *evt)
{
    if (evt->type == SDL_QUIT)
    {
        _running = false;
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void CAApp::OnLoop()
{
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void CAApp::OnRender()
{
    SDL_SetRenderDrawColor(_renderer, 96, 128, 255, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void CAApp::OnCleanup()
{
    SDL_Quit();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    CAApp app;
    return app.OnExecute();
}
