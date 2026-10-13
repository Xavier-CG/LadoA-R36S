
#include "FPSCounter.h"

#include <string>

void FPSCounter::actualizar(float deltaTime) {
    tiempoAcumulado += deltaTime;
    fotogramas++;

    if (tiempoAcumulado >= 1.0f) {
        fps = static_cast<int>(
            fotogramas / tiempoAcumulado
        );

        fotogramas = 0;
        tiempoAcumulado = 0.0f;
    }
}

void FPSCounter::mostrarEnTitulo(SDL_Window* ventana) {
    std::string titulo =
        "Lado A | FPS: " + std::to_string(fps);

    SDL_SetWindowTitle(ventana, titulo.c_str());
}
