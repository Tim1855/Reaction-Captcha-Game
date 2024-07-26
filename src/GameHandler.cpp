#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include "GameHandler.hpp"
#include "GameMode1.hpp"
#include "GameMode2.hpp"
#include "Config.hpp"

// Konstruktor, initialisiert alle Mitglieder auf Standardwerte oder Null.
GameHandler::GameHandler() : m_currentGameMode(nullptr), m_numImagesToDisplay(0), m_imageClicked(false), m_sequence{ 0 } {
}

// Destruktor der GameHandler-Klasse.
GameHandler::~GameHandler() {
    // Automatische Aufräumvorgänge finden hier statt.
}

// Initialisiert das Spiel mit den übergebenen Parametern.
void GameHandler::initializeGame(const std::string& playerName, int numImages, int sequence, int gameMode) {
    m_playerName = playerName; // Setzt den Namen des Spielers.
    m_numImagesToDisplay = numImages; // Setzt die Anzahl der Bilder, die gespielt werden sollen.
    m_sequence = sequence; // Setzt die Sequenznummer für die Bilderauswahl.
    m_gameMode = gameMode; // Setzt den Spielmodus.

    // Stream zur Formatierung der Sequenznummer als vierstellige Zahl mit führenden Nullen.
    std::ostringstream sequenceStream;
    sequenceStream << std::setw(4) << std::setfill('0') << sequence; 
    std::string sequenceString = sequenceStream.str(); // Konvertiert die formatierte Sequenznummer in einen String.
    std::cout << sequenceString; // Gibt die formatierte Sequenznummer aus.

    // Bildet den vollständigen Pfad zum Bilderordner.
    imageFolderPath = imageFolder + sequenceString;

    // Entscheidet basierend auf dem Spielmodus, welches Spielmodus-Objekt erstellt wird.
    if (m_gameMode == 1) {
        // Erstellt ein neues GameMode1-Objekt, wenn der Spielmodus 1 gewählt wurde.
        m_currentGameMode = std::make_unique<GameMode1>(imageFolderPath, bboxFolderPath);
    }
    else if (m_gameMode == 2) {
        // Erstellt ein neues GameMode2-Objekt, wenn der Spielmodus 2 gewählt wurde.
        m_currentGameMode = std::make_unique<GameMode2>(imageFolderPath, bboxFolderPath);
    }
    // Setzt die Rückruffunktion für Mausklick-Ereignisse.
    m_currentGameMode->setMouseCallback(&m_imageClicked);
}


void GameHandler::startGame() {
    // Startet den ausgewählten Spielmodus mit der spezifizierten Sequenz und Anzahl der Bilder
    m_currentGameMode->startMode(m_sequence, m_numImagesToDisplay);

    // Logik für den Spielmodus 1
    if (m_gameMode == 1) {
        // Durchläuft jedes Bild der festgelegten Anzahl
        for (int i = 0; i < m_numImagesToDisplay; ++i) {
            // Lädt das Bild und die entsprechenden Bounding Boxes
            m_currentGameMode->loadImageAndBoundingBox(m_sequence, i);
            // Setzt den Status für das Bild-Klick-Ereignis zurück
            m_imageClicked = 0;
            // Speichert die Startzeit für die Reaktionszeitmessung
            auto startTime = std::chrono::high_resolution_clock::now();

            // Wartet auf einen Klick innerhalb der festgelegten Zeitgrenze
            while (!m_imageClicked) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

                // Prüft, ob die maximale Wartezeit überschritten wurde
                if (duration >= 3) {
                    std::cout << "Bild " << i + 1 << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(5.0); // Fügt eine Strafzeit hinzu
                    break;
                }

                cv::waitKey(30); // Kurzes Warten auf Benutzerinteraktion

                // Verarbeitet die Reaktionszeit, wenn ein Klick erkannt wurde
                if (m_imageClicked) {
                    auto endTime = std::chrono::high_resolution_clock::now();
                    auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
                    // Prüft, ob der Klick innerhalb einer Bounding Box erfolgte
                    if (static_cast<GameMode1*>(m_currentGameMode.get())->lastClickInBoundingBox()) {
                        std::cout << "Bild " << i + 1 << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
                        m_reactionTimes.push_back(reactionTime); // Speichert die gemessene Reaktionszeit
                    }
                    else {
                        std::cout << "Bild " << i + 1 << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
                        m_reactionTimes.push_back(reactionTime + 5.0); // Fügt eine Strafzeit hinzu, wenn außerhalb geklickt wurde
                    }
                }
            }
        }
        endGame(); // Beendet das Spiel
    }
    // Logik für den Spielmodus 2
    else if (m_gameMode == 2) {
        // Ähnlich wie Modus 1, aber mit zusätzlicher Logik für die Reaktionszeit nach einem Farbwechsel (nicht vollständig dargestellt)
        for (int i = 0; i < m_numImagesToDisplay; ++i) {
            m_currentGameMode->loadImageAndBoundingBox(m_sequence, i);
            m_imageClicked = 0;
            m_spacebarPressed = 0;
            auto startTime = std::chrono::high_resolution_clock::now();

            while (true) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                m_duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

                int key = cv::waitKey(30); // Überprüft kurzzeitig die Benutzerinteraktion
                if (key == 32) { // Überprüft, ob die Leertaste gedrückt wurde
                    m_spacebarPressed = 1;
                    break;
                }

                if (m_duration >= 3) {
                    std::cout << "Bild " << i + 1 << ": Keine Reaktion : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(5.0); // Fügt eine Strafzeit hinzu
                    break;
                }
            }

            if (m_spacebarPressed) {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
                if (static_cast<GameMode2*>(m_currentGameMode.get())->lastClickInBoundingBox()) {
                    std::cout << "Bild " << i + 1 << ": Reaktionszeit: " << reactionTime << " Sekunden" << std::endl;
                    m_reactionTimes.push_back(reactionTime);
                }
                else {
                    std::cout << "Bild " << i + 1 << ": Fehlklick : 5 Sekunden Strafe" << std::endl;
                    m_reactionTimes.push_back(reactionTime + 5.0); // Fügt eine zusätzliche Strafzeit hinzu
                }
            }
        }
    }
    endGame(); // Beendet das Spiel und ruft die Endspiel-Routine auf
}

// Methode zum Beenden des Spiels und Aufräumen der Ressourcen.
void GameHandler::endGame() {
    std::cout << "Game ended." << std::endl; // Informiert den Benutzer über das Ende des Spiels.
    cv::destroyAllWindows(); // Schließt alle geöffneten OpenCV-Fenster.
    giveFeedback(); // Ruft die Methode auf, um Feedback zum Spielergebnis zu geben.
}

// Methode zur Bereitstellung von Feedback basierend auf den gesammelten Reaktionszeiten.
void GameHandler::giveFeedback() {
    std::cout << "Player: " << m_playerName << std::endl; // Gibt den Namen des Spielers aus.
    std::cout << "Feedback: Spiel beendet." << std::endl; // Bestätigt das Ende des Spiels.

    // Prüft, ob Reaktionszeiten vorhanden sind, um Feedback zu geben.
    if (!m_reactionTimes.empty()) {
        // Sortiert die Reaktionszeiten. Zeiten, die größer als 0 sind, werden bevorzugt und in aufsteigender Reihenfolge sortiert.
        std::sort(m_reactionTimes.begin(), m_reactionTimes.end(), [](double a, double b) { return a > 0 && (b < 0 || a < b); });

        double sum = 0; // Variable zur Summierung der Reaktionszeiten.
        int count = 0; // Zähler für gültige Reaktionszeiten.
        for (double time : m_reactionTimes) {
            sum += time; // Summiert alle Zeiten einschließlich Strafen.
            if (time >= 0) { // Zählt nur gültige Reaktionszeiten.
                count++;
            }
        }
        double average = (count > 0) ? sum / m_reactionTimes.size() : 0; // Berechnet den Durchschnitt der Reaktionszeiten.

        std::cout << "Beste Reaktionszeiten:" << std::endl;
        // Gibt die drei besten Reaktionszeiten aus.
        for (int i = 0; i < std::min(3, static_cast<int>(m_reactionTimes.size())); ++i) {
            if (m_reactionTimes[i] >= 0) {
                std::cout << i + 1 << ". " << m_reactionTimes[i] << " Sekunden" << std::endl;
            }
            else {
                std::cout << i + 1 << ". " << "Keine Reaktion : 5 Sekunden Strafe" << std::endl;
            }
        }
        std::cout << "Durchschnittliche Reaktionszeit: " << average << " Sekunden" << std::endl;
    }
    else {
        std::cout << "Keine Reaktionen registriert." << std::endl; // Meldet, wenn keine Reaktionen registriert wurden.
    }
}
