#include "Gui.hpp"

Gui::Gui(const std::string& windowName) : m_windowName(windowName) {
    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
}

void Gui::showImage(const cv::Mat& image) const {
    cv::imshow(m_windowName, image);
}

void Gui::drawBoundingBox(const BoundingBox& bbox, const cv::Scalar& color) const {
    cv::rectangle(cv::Mat(), cv::Point(bbox.getX1(), bbox.getY1()), cv::Point(bbox.getX2(), bbox.getY2()), color, 2);
}
