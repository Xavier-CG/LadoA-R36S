
#include <SDL2/SDL.h>
#include <iostream>

int main() {

    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL: " << SDL_GetError() << '\n';
        return 1;
    }

    // Crear ventana de 640x480 (resolucion R36S)
    SDL_Window* ventana = SDL_CreateWindow(
        "Lado A",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (!ventana) {
        std::cerr << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // Crear renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(
        ventana, -1, SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        renderer = SDL_CreateRenderer(
            ventana, -1, SDL_RENDERER_SOFTWARE
        );
    }

    if (!renderer) {
        std::cerr << SDL_GetError() << '\n';
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Album seleccionado (0, 1 o 2)
    int album = 1;
    bool ejecutando = true;

    // Bucle principal
    while (ejecutando) {

        SDL_Event evento;

        // Procesar controles
        while (SDL_PollEvent(&evento)) {

            if (evento.type == SDL_QUIT) {
                ejecutando = false;
            }

            if (evento.type == SDL_KEYDOWN) {

                switch (evento.key.keysym.sym) {

                    case SDLK_ESCAPE:
                        ejecutando = false;
                        break;

                    case SDLK_LEFT:
                        if (album > 0) {
                            album--;
                        }
                        break;

                    case SDLK_RIGHT:
                        if (album < 2) {
                            album++;
                        }
                        break;
                }
            }
        }

        // Fondo oscuro
        SDL_SetRenderDrawColor(renderer, 16, 19, 24, 255);
        SDL_RenderClear(renderer);

        // Dibujar los tres albumes
        for (int i = 0; i < 3; i++) {

            // Distancia respecto al album seleccionado
            int distancia = i - album;

            // Album seleccionado centrado
            int centroX = 320 + distancia * 175;

            // Tamano segun posicion
            int tamano = (distancia == 0) ? 150 : 110;

            // Centrar vertical y horizontalmente
            SDL_Rect portada = {
                centroX - tamano / 2,
                240 - tamano / 2,
                tamano,
                tamano
            };

            // Colores diferentes para cada album
            if (i == 0) {
                SDL_SetRenderDrawColor(
                    renderer, 190, 85, 105, 255
                );
            } else if (i == 1) {
                SDL_SetRenderDrawColor(
                    renderer, 90, 145, 195, 255
                );
            } else {
                SDL_SetRenderDrawColor(
                    renderer, 115, 175, 130, 255
                );
            }

            SDL_RenderFillRect(renderer, &portada);

            // Borde blanco del album seleccionado
            if (i == album) {
                SDL_SetRenderDrawColor(
                    renderer, 240, 240, 240, 255
                );
                SDL_RenderDrawRect(renderer, &portada);
            }
        }

        // Actualizar pantalla
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}
