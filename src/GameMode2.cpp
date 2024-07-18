#include "GameMode2.hpp"
#include "Gui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

// Konstruktor für GameMode2, initialisiert die Mitglieder mit Standardwerten oder Null.
GameMode2::GameMode2(const std::string& imageFolderPath, const std::string& bboxFolderPath)
    : m_imageFolderPath(imageFolderPath), m_bboxFolderPath(bboxFolderPath), m_currentSequence(0), m_currentIndex(0), m_imageClicked(nullptr) {
}

// Destruktor für GameMode2.
GameMode2::~GameMode2() {
}

// Lädt die Bounding Boxes für die angegebene Sequenznummer.
bool GameMode2::loadBoundingBoxes(int sequence) {
    m_currentSequence = sequence; // Aktualisiert die aktuelle Sequenznummer.

    // Erstellt den vollständigen Pfad zur Bounding Box-Datei.
    std::ostringstream bboxFilePathStream;
    bboxFilePathStream << m_bboxFolderPath << "/" << std::setw(4) << std::setfill('0') << sequence << ".txt";
    std::string bboxFilePath = bboxFilePathStream.str();

    // Versucht, die Datei zu öffnen.
    std::ifstream infile(bboxFilePath);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open bounding box file: " << bboxFilePath << std::endl;
        return false;
    }

    // Löscht frühere Bounding Boxes und liest neue ein.
    m_boundingBoxes.clear();
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int frameIndex, objIndex, truncation, occlusion;
        std::string type;
        float alpha, x1, y1, x2, y2, h, w, l, t1, t2, t3, rotY;
        if (!(iss >> frameIndex >> objIndex >> type >> truncation >> occlusion >> alpha >> x1 >> y1 >> x2 >> y2 >> h >> w >> l >> t1 >> t2 >> t3 >> rotY)) {
            continue; // Springt zum nächsten Eintrag, wenn die Zeile nicht korrekt geparsed werden konnte.
        }

        if (type == "DontCare") {
            continue; // Ignoriert Objekte vom Typ "DontCare".
        }

        // Fügt die Bounding Box zur Liste hinzu.
        BoundingBox bbox(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
        if (m_boundingBoxes.size() <= frameIndex) {
            m_boundingBoxes.resize(frameIndex + 1);
        }
        m_boundingBoxes[frameIndex].push_back(cv::Rect(cv::Point(bbox.getX1(), bbox.getY1()), cv::Point(bbox.getX2(), bbox.getY2())));
    }

    return true;
}

// Lädt das Bild und die zugehörigen Bounding Boxes für eine gegebene Sequenz und Index.
void GameMode2::loadImageAndBoundingBox(int sequence, int index) {
    if (!loadBoundingBoxes(sequence)) {
        return;
    }
    m_currentIndex = index; // Aktualisiert den aktuellen Index.

    // Bildet den Pfad zum Bild und lädt es.
    std::ostringstream imagePathStream;
    imagePathStream << m_imageFolderPath << "/" << std::setw(6) << std::setfill('0') << index << ".png";
    std::string imagePath = imagePathStream.str();

    m_currentImage = cv::imread(imagePath);
    if (m_currentImage.empty()) {
        std::cerr << "Error: Image not found: " << imagePath << std::endl;
        return;
    }

    if (!filterBoundingBoxesForFrame(index)) {
        return;
    }

    m_redBoundingBoxSet = 0; // Setzt den Zustand der roten Bounding Box zurück.
    display(); // Zeigt das Bild an.
}

// Filtert Bounding Boxes für ein spezifisches Frame.
bool GameMode2::filterBoundingBoxesForFrame(int frameIndex) {
    if (frameIndex < 0 || frameIndex >= static_cast<int>(m_boundingBoxes.size())) {
        std::cerr << "Error: Invalid frame index for bounding box" << std::endl;
        return false;
    }

    m_currentBoundingBoxes.clear();
    for (const auto& bbox : m_boundingBoxes[frameIndex]) {
        m_currentBoundingBoxes.push_back(bbox);
    }

    return !m_currentBoundingBoxes.empty();
}

// Startet den Modus, bereitet das Spiel für die Ausführung vor.
void GameMode2::startMode(int sequence, int numImages) {
    std::cout << "GameMode2 started" << std::endl; // Bestätigung, dass der Modus gestartet wurde.
}

// Zeigt das Bild und alle zugehörigen Bounding Boxes.
void GameMode2::display() {
    if (m_currentImage.empty()) return; // Überprüft, ob das Bild geladen ist.

    cv::Mat displayImage = m_currentImage.clone(); // Erstellt eine Kopie des aktuellen Bildes zur Anzeige.
    for (const auto& bbox : m_currentBoundingBoxes) {
        cv::Scalar color = (bbox == m_redBoundingBox) ? cv::Scalar(0, 0, 255) : cv::Scalar(255, 0, 0); // Rot für die Ziel-Bounding Box, sonst Blau.
        cv::rectangle(displayImage, bbox, color, 2); // Zeichnet jede Bounding Box.
    }

    cv::imshow("Game Window", displayImage); // Zeigt das Bild im Fenster an.
    updateRedBoundingBox(); // Aktualisiert die rote Bounding Box zufällig.
    // Setzt den Maus-Callback für das Spielfenster.
    cv::setMouseCallback("Game Window", [](int event, int x, int y, int flags, void* userdata) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            static_cast<GameMode2*>(userdata)->handleMouseClick(x, y);
        }
    }, this);
}

// Aktualisiert die rote Bounding Box nach einer zufälligen Verzögerung.
void GameMode2::updateRedBoundingBox() {
    if (!m_redBoundingBoxSet) {
        int delay = 1000 + (std::rand() % 1000); // 1-2 Sekunden Verzögerung.
        cv::waitKey(delay); // Wartet für die angegebene Verzögerung.
        if (!m_currentBoundingBoxes.empty()) {
            std::random_device rd; // Zufallszahlengenerator.
            std::mt19937 gen(rd()); // Generator für Zufallszahlen.
            std::uniform_int_distribution<> dis(0, m_currentBoundingBoxes.size() - 1); // Gleichverteilung.
            m_redBoundingBox = m_currentBoundingBoxes[dis(gen)]; // Wählt eine zufällige Bounding Box.
            m_redBoundingBoxSet = 1; // Setzt, dass die rote Bounding Box festgelegt wurde.
            display(); // Zeigt das Bild erneut an, um die aktualisierte Bounding Box zu reflektieren.
        }
    }
}

// Setzt die Callback-Funktion für Mausklicks.
void GameMode2::setMouseCallback(bool* imageClicked) {
    m_imageClicked = imageClicked;
}

// Verarbeitet Mausklicks und prüft, ob sie innerhalb der roten Bounding Box erfolgten.
void GameMode2::handleMouseClick(int x, int y) {
    if (m_redBoundingBox.contains(cv::Point(x, y))) {
        m_lastClickInBoundingBox = true; // Bestätigt einen Treffer innerhalb der Bounding Box.
    }
    else {
        m_lastClickInBoundingBox = false; // Kein Treffer, Klick außerhalb der Bounding Box.
    }
    *m_imageClicked = true; // Setzt das Klick-Ereignis, unabhängig vom Trefferstatus.
}

// Gibt zurück, ob der letzte Klick innerhalb der Bounding Box erfolgte.
bool GameMode2::lastClickInBoundingBox() const {
    return m_lastClickInBoundingBox;
}
