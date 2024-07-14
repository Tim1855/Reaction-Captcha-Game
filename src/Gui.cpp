#include "Gui.hpp"
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

Gui::Gui(const std::string& windowName) : m_windowName(windowName) {
    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
    cv::setWindowProperty(m_windowName, cv::WND_PROP_TOPMOST, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Kurze Pause, um sicherzustellen, dass das Fenster im Vordergrund ist
}

void Gui::showImage(const cv::Mat& image) const {
    cv::imshow(m_windowName, image);
    cv::setWindowProperty(m_windowName, cv::WND_PROP_TOPMOST, 1); // Setzen Sie das Fenster erneut in den Vordergrund
    cv::waitKey(1); // Kurzes Warten, um sicherzustellen, dass das Fenster angezeigt wird
}

void Gui::drawBoundingBox(const BoundingBox& bbox, const cv::Scalar& color) const {
    cv::rectangle(cv::Mat(), cv::Point(bbox.getX1(), bbox.getY1()), cv::Point(bbox.getX2(), bbox.getY2()), color, 2);
}
