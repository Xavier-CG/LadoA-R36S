
#include "CoverFlow.h"

#include <cmath>
#include <algorithm>

void CoverFlow::anterior() {
    if (albumSeleccionado > 0) {
        albumSeleccionado--;
    }
}

void CoverFlow::siguiente() {
    if (albumSeleccionado < TOTAL_ALBUMES - 1) {
        albumSeleccionado++;
    }
}

void CoverFlow::actualizar(float deltaTime) {

    float destino = static_cast<float>(albumSeleccionado);

    // Interpolacion suave independiente de los FPS
    float factor = 1.0f - std::exp(-velocidadAnimacion * deltaTime);

    posicionActual += (destino - posicionActual) * factor;

    // Evitar movimientos diminutos al finalizar
    if (std::abs(destino - posicionActual) < 0.001f) {
        posicionActual = destino;
    }
}

void CoverFlow::dibujar(SDL_Renderer* renderer) {

    const SDL_Color colores[TOTAL_ALBUMES] = {
        {214, 107, 120, 255},
        {213, 154,  84, 255},
        {157, 140, 201, 255},
        { 94, 158, 174, 255},
        {142, 174, 120, 255},
        {197, 141, 186, 255},
        { 96, 137, 187, 255},
        {187, 163, 109, 255},
        {157, 119, 113, 255}
    };

    // Dibujar de atras hacia adelante:
    // primero los laterales y al final los centrales.
    for (int capa = 2; capa >= 0; capa--) {
        for (int i = 0; i < TOTAL_ALBUMES; i++) {

            float distancia = static_cast<float>(i) - posicionActual;
            float distanciaAbs = std::abs(distancia);

            if (distanciaAbs > 2.7f) {
                continue;
            }

            // Elegir capa segun distancia
            int capaAlbum = std::min(2, static_cast<int>(distanciaAbs + 0.5f));

            if (capaAlbum != capa) {
                continue;
            }

            // Tamano progresivo
            float tamano = 150.0f - distanciaAbs * 35.0f;
            tamano = std::max(65.0f, tamano);

            // Desplazamiento horizontal progresivo
            float centroX = 320.0f + distancia * 125.0f;

            SDL_Rect portada = {
                static_cast<int>(centroX - tamano / 2.0f),
                static_cast<int>(240.0f - tamano / 2.0f),
                static_cast<int>(tamano),
                static_cast<int>(tamano)
            };

            SDL_Color color = colores[i];

            SDL_SetRenderDrawColor(
                renderer,
                color.r, color.g, color.b, 255
            );

            SDL_RenderFillRect(renderer, &portada);

            // Decoracion individual de cada album
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

            SDL_Rect linea = {
                portada.x + 12,
                portada.y + 18,
                std::max(10, portada.w / 3),
                4
            };

            SDL_RenderFillRect(renderer, &linea);

            // Marcar el album seleccionado
            if (i == albumSeleccionado) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &portada);
            }
        }
    }
}
