#pragma once

#include <SDL2/SDL.h>

class CoverFlow {
public:
    void anterior();
    void siguiente();
    void dibujar(SDL_Renderer* renderer);

private:
    int albumSeleccionado = 1;
};