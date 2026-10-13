# LadoA-R36S

Reproductor de musica open source inspirado en Cover Flow,
desarrollado para consolas portatiles R36S compatibles.

## Caracteristicas planeadas

- Navegacion de albumes mediante Cover Flow
- Reproduccion de musica local
- Compatibilidad con MP3 y FLAC
- Visualizadores musicales
- Interfaz adaptada a controles fisicos

## Estado del proyecto

Prototipo inicial en C++17 y SDL2.

Actualmente funciona en Debian Linux x86_64.
La compatibilidad con ArkOS ARM64 aun no ha sido verificada.

## Compilacion en Debian

Instalar dependencias:

    sudo apt install build-essential cmake pkg-config libsdl2-dev

Compilar:

    cmake -S . -B build
    cmake --build build

Ejecutar desde el escritorio grafico:

    ./build/ladoa
