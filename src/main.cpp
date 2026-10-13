
#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>

#include "ui/CoverFlow.h"

int main()
{

    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Error SDL: " << SDL_GetError() << '\n';
        return 1;
    }

    // Crear ventana
    SDL_Window *ventana = SDL_CreateWindow(
        "Lado A",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN);

    if (!ventana)
    {
        std::cerr << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // Crear renderizador
    SDL_Renderer *renderer = SDL_CreateRenderer(
        ventana, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        renderer = SDL_CreateRenderer(
            ventana, -1, SDL_RENDERER_SOFTWARE);
    }

    if (!renderer)
    {
        std::cerr << SDL_GetError() << '\n';
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Crear nuestro carrusel
    CoverFlow coverFlow;

    bool ejecutando = true;
    Uint64 tiempoAnterior = SDL_GetPerformanceCounter();

    while (ejecutando)
    {

        Uint64 tiempoActual = SDL_GetPerformanceCounter();

        float deltaTime = static_cast<float>(
                              tiempoActual - tiempoAnterior) /
                          static_cast<float>(SDL_GetPerformanceFrequency());

        tiempoAnterior = tiempoActual;

        // Limitar saltos grandes al volver de una pausa
        deltaTime = std::min(deltaTime, 0.05f);

        coverFlow.actualizar(deltaTime);

        SDL_Event evento;

        while (SDL_PollEvent(&evento))
        {

            if (evento.type == SDL_QUIT)
            {
                ejecutando = false;
            }

            if (evento.type == SDL_KEYDOWN)
            {

                switch (evento.key.keysym.sym)
                {

                case SDLK_ESCAPE:
                    ejecutando = false;
                    break;

                case SDLK_LEFT:
                    coverFlow.anterior();
                    break;

                case SDLK_RIGHT:
                    coverFlow.siguiente();
                    break;
                }
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 16, 19, 24, 255);
        SDL_RenderClear(renderer);

        // Dibujar nuestro modulo CoverFlow
        coverFlow.dibujar(renderer);

        // Mostrar resultado
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}
