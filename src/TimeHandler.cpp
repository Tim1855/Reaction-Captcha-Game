#include "TimeHandler.hpp"  // Inkludieren der Header-Datei für die TimeHandler-Klasse

// Konstruktor der TimeHandler-Klasse, initialisiert die Startzeit
TimeHandler::TimeHandler() : m_startTime() {}

// Startet die Zeitmessung, indem der aktuelle Zeitpunkt gespeichert wird
void TimeHandler::start() {
    // Speichert den aktuellen hochpräzisen Zeitpunkt in m_startTime
    m_startTime = std::chrono::high_resolution_clock::now();
}

// Stoppt die Zeitmessung und berechnet die Dauer in Sekunden
double TimeHandler::stop() {
    // Erfasst den aktuellen Zeitpunkt als Endezeit
    auto endTime = std::chrono::high_resolution_clock::now();
    // Berechnet die Differenz zwischen Start- und Endzeit in Millisekunden
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_startTime).count();
    // Konvertiert die Dauer von Millisekunden in Sekunden und gibt diese zurück
    return duration / 1000.0;
}
