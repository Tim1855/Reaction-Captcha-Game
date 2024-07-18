#include "Image.hpp" 

// Konstruktor der Image-Klasse, der den Dateipfad als Argument nimmt.
Image::Image(const std::string& filePath) {
    // Lädt ein Bild von der angegebenen Datei und speichert es in m_image.
    // cv::imread ist eine OpenCV-Funktion, die ein Bild aus der Datei liest.
    m_image = cv::imread(filePath);
}

// Getter-Methode, um das Bildobjekt zurückzugeben.
cv::Mat Image::getImage() const {
    // Gibt die private Mitgliedsvariable m_image zurück.
    // cv::Mat ist ein OpenCV-Datentyp zur Speicherung von Bildern.
    return m_image;
}
