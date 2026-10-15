
#include "PerformanceLogger.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

PerformanceLogger::PerformanceLogger() {
    try {
        fs::create_directories("logs");

        // Crear un identificador con fecha y hora.
        const auto ahora = std::chrono::system_clock::now();
        const std::time_t tiempo =
            std::chrono::system_clock::to_time_t(ahora);

        std::tm fecha{};
#ifdef _WIN32
        localtime_s(&fecha, &tiempo);
#else
        localtime_r(&tiempo, &fecha);
#endif

        std::ostringstream nombre;
        nombre << std::put_time(&fecha, "%Y-%m-%d_%H%M%S");

        const std::string base = nombre.str();
        nombreSesion = base;

        // Evitar sobrescribir una sesion con el mismo segundo.
        int numero = 1;

        while (
            fs::exists("logs/performance_" + nombreSesion + ".csv") ||
            fs::exists("logs/resumen_" + nombreSesion + ".txt")
        ) {
            nombreSesion = base + "_" + std::to_string(numero++);
        }

        const std::string ruta =
            "logs/performance_" + nombreSesion + ".csv";

        archivo.open(ruta);

        if (archivo.is_open()) {
            archivo << "segundo,fps,frametime_ms\n";

            std::cout
                << "[PerformanceLogger] Registro iniciado: "
                << ruta << "\n";
        } else {
            std::cerr
                << "[PerformanceLogger] No se pudo crear el CSV\n";
        }
    } catch (const fs::filesystem_error& error) {
        std::cerr
            << "[PerformanceLogger] Error: "
            << error.what() << "\n";
    }
}

void PerformanceLogger::registrar(float deltaTime, float fps) {
    // Por ahora los FPS se calculan a partir de deltaTime.
    // Conservamos el parametro para no cambiar main.cpp.
    (void)fps;

    if (!std::isfinite(deltaTime) || deltaTime <= 0.0f) {
        return;
    }

    tiempoTotal += deltaTime;
    tiempoIntervalo += deltaTime;

    fotogramasTotales++;
    fotogramasIntervalo++;

    if (tiempoIntervalo >= 1.0) {
        guardarMuestra();
    }
}

void PerformanceLogger::guardarMuestra() {
    if (fotogramasIntervalo == 0 || tiempoIntervalo <= 0.0) {
        return;
    }

    const float fpsPromedio = static_cast<float>(
        fotogramasIntervalo / tiempoIntervalo
    );

    const float frametimeMs = static_cast<float>(
        1000.0 * tiempoIntervalo / fotogramasIntervalo
    );

    if (archivo.is_open()) {
        archivo << std::fixed << std::setprecision(2)
                << tiempoTotal << ","
                << fpsPromedio << ","
                << frametimeMs << "\n";
    }

    if (muestras == 0) {
        fpsMinimo = fpsPromedio;
        fpsMaximo = fpsPromedio;
    } else {
        fpsMinimo = std::min(fpsMinimo, fpsPromedio);
        fpsMaximo = std::max(fpsMaximo, fpsPromedio);
    }

    muestras++;

    tiempoIntervalo = 0.0;
    fotogramasIntervalo = 0;
}

void PerformanceLogger::guardarResumen() {
    // Incluir el ultimo intervalo, aunque dure menos de 1 s.
    if (fotogramasIntervalo > 0) {
        guardarMuestra();
    }

    const double fpsGeneral =
        tiempoTotal > 0.0
            ? fotogramasTotales / tiempoTotal
            : 0.0;

    const double frametimeGeneral =
        fotogramasTotales > 0
            ? 1000.0 * tiempoTotal / fotogramasTotales
            : 0.0;

    std::ostringstream resumen;

    resumen << std::fixed << std::setprecision(2);

    resumen << "================================\n";
    resumen << "       LADO A - R36S\n";
    resumen << "    RESUMEN DE RENDIMIENTO\n";
    resumen << "================================\n\n";

    resumen << "Sesion:          " << nombreSesion << "\n";
    resumen << "Duracion:        " << tiempoTotal << " s\n";
    resumen << "Fotogramas:      " << fotogramasTotales << "\n";
    resumen << "FPS promedio:    " << fpsGeneral << "\n";
    resumen << "FPS minimo:      " << fpsMinimo << "\n";
    resumen << "FPS maximo:      " << fpsMaximo << "\n";
    resumen << "Frametime medio: " << frametimeGeneral << " ms\n";
    resumen << "Muestras:        " << muestras << "\n";

    resumen << "\nNota: FPS minimo y maximo son\n";
    resumen << "promedios por intervalo.\n";

    resumen << "\n================================\n";

    std::cout << "\n" << resumen.str();

    if (!nombreSesion.empty()) {
        std::ofstream archivoResumen(
            "logs/resumen_" + nombreSesion + ".txt"
        );

        if (archivoResumen.is_open()) {
            archivoResumen << resumen.str();
            archivoResumen.close();

            std::cout
                << "[PerformanceLogger] Resumen guardado\n";
        } else {
            std::cerr
                << "[PerformanceLogger] Error al guardar resumen\n";
        }
    }
}

PerformanceLogger::~PerformanceLogger() {
    guardarResumen();

    if (archivo.is_open()) {
        archivo.flush();
        archivo.close();
    }
}
