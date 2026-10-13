
#pragma once

#include <SDL2/SDL.h>

class CoverFlow {
public:
    void anterior();
    void siguiente();

    void actualizar(float deltaTime);
    void dibujar(SDL_Renderer* renderer);

private:
    static constexpr int TOTAL_ALBUMES = 9;

    int albumSeleccionado = 4;

    // Posicion visual animada
    float posicionActual = 4.0f;

    // Velocidad de desplazamiento
    float velocidadAnimacion = 8.0f;
};
