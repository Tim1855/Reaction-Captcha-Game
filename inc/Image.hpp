#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp> // Einbindung von OpenCV zur Bildverarbeitung
#include <string> // Einbindung der Standardbibliothek für Strings

class Image {
public:
    Image(const std::string& filePath); // Konstruktor, der den Pfad zum Bild als Parameter nimmt
    cv::Mat getImage() const; // Methode, um das OpenCV Bildobjekt zurückzugeben

private:
    cv::Mat m_image; // Private Variable zum Speichern des Bildes
};

#endif // IMAGE_HPP
