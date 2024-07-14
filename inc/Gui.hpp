#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include "BoundingBox.hpp"

class Gui {
public:
    Gui(const std::string& windowName);
    void showImage(const cv::Mat& image) const;
    void drawBoundingBox(const BoundingBox& bbox, const cv::Scalar& color) const;

private:
    std::string m_windowName;
};

#endif // GUI_HPP
