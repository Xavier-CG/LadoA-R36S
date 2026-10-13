
#include "CoverFlow.h"

// Seleccionar el album anterior
void CoverFlow::anterior() {
    if (albumSeleccionado > 0) {
        albumSeleccionado--;
    }
}

// Seleccionar el siguiente album
void CoverFlow::siguiente() {
    if (albumSeleccionado < 2) {
        albumSeleccionado++;
    }
}

// Dibujar los albumes en pantalla
void CoverFlow::dibujar(SDL_Renderer* renderer) {

    for (int i = 0; i < 3; i++) {

        // Distancia respecto al album seleccionado
        int distancia = i - albumSeleccionado;

        // Posicion horizontal
        int centroX = 320 + distancia * 175;

        // Album central mas grande
        int tamano = (distancia == 0) ? 150 : 110;

        SDL_Rect portada = {
            centroX - tamano / 2,
            240 - tamano / 2,
            tamano,
            tamano
        };

        // Color individual de cada album
        if (i == 0) {
            SDL_SetRenderDrawColor(renderer, 190, 85, 105, 255);
        } else if (i == 1) {
            SDL_SetRenderDrawColor(renderer, 90, 145, 195, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 115, 175, 130, 255);
        }

        SDL_RenderFillRect(renderer, &portada);

        // Resaltar el album seleccionado
        if (i == albumSeleccionado) {
            SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            SDL_RenderDrawRect(renderer, &portada);
        }
    }
}
