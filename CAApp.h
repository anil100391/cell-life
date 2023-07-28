#ifndef _CAAPP_H_
#define _CAAPP_H_

#include <SDL2/SDL.h>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class CAApp
{
public:
    CAApp() = default;
    ~CAApp() = default;

    int OnExecute();

    bool OnInit();
    void OnEvent(SDL_Event* evt);
    void OnLoop();
    void OnRender();
    void OnCleanup();

private:

    bool            _running  = true;
    SDL_Renderer*   _renderer = nullptr;
    SDL_Window*     _window   = nullptr;
};

#endif // _CAAPP_H_
