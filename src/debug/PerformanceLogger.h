
#pragma once

#include <fstream>
#include <string>

class PerformanceLogger {
public:
    PerformanceLogger();
    ~PerformanceLogger();

    void registrar(float deltaTime, float fps);

private:
    void guardarMuestra();
    void guardarResumen();

    std::ofstream archivo;
    std::string nombreSesion;

    double tiempoTotal = 0.0;
    double tiempoIntervalo = 0.0;

    unsigned long long fotogramasTotales = 0;
    unsigned int fotogramasIntervalo = 0;

    float fpsMinimo = 0.0f;
    float fpsMaximo = 0.0f;
    unsigned int muestras = 0;
};
