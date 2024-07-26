#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include "BoundingBox.hpp"

class Gui {
public:
    Gui(const std::string& windowName);
    void showImage(const cv::Mat& image) const; // Methode zum Anzeigen eines Bildes
    void drawBoundingBox(const BoundingBox& bbox, const cv::Scalar& color) const; // Methode zum Zeichnen einer Bounding Box auf einem Bild

private:
    std::string m_windowName;
};

#endif // GUI_HPP
