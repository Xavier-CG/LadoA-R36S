
#pragma once

#include <SDL2/SDL.h>

class FPSCounter {
public:
    void actualizar(float deltaTime);
    void mostrarEnTitulo(SDL_Window* ventana);

private:
    float tiempoAcumulado = 0.0f;
    int fotogramas = 0;
    int fps = 0;
};
