#include "Gui.hpp"  
#include <opencv2/opencv.hpp>  
#include <thread>  
#include <chrono>  

// Konstruktor, der ein Fenster mit gegebenem Namen erstellt
Gui::Gui(const std::string& windowName) : m_windowName(windowName) {
    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);  // Erstellt ein neues Fenster mit automatischer Größenanpassung
    cv::setWindowProperty(m_windowName, cv::WND_PROP_TOPMOST, 1);  // Setzt das Fenster immer oben auf dem Desktop
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Kurze Pause, um sicherzustellen, dass das Fenster im Vordergrund ist
}

// Methode zum Anzeigen eines Bildes im GUI-Fenster
void Gui::showImage(const cv::Mat& image) const {
    cv::imshow(m_windowName, image);  // Zeigt das Bild im Fenster an
    cv::setWindowProperty(m_windowName, cv::WND_PROP_TOPMOST, 1);  // Stellt sicher, dass das Fenster weiterhin im Vordergrund bleibt
    cv::waitKey(1);  // Kurzes Warten, um das GUI-Rendering zu ermöglichen
}

// Methode zum Zeichnen einer Bounding Box auf einem Bild
void Gui::drawBoundingBox(const BoundingBox& bbox, const cv::Scalar& color) const {
    // Zeichnet ein Rechteck auf dem Bild basierend auf den Koordinaten der BoundingBox
    cv::rectangle(cv::Mat(), cv::Point(bbox.getX1(), bbox.getY1()), cv::Point(bbox.getX2(), bbox.getY2()), color, 2);
}
