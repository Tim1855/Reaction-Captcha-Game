#include "Gui.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


Gui::Gui() {}// Constructor
Gui::~Gui() {}// Destructor

void Gui::initWindow() const { // Initialize the GUI window
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
}

void Gui::showImage(const Image& image) const { // Display the image
    cv::Mat displayImage = image.getImage().clone();
    drawBoundingBoxes(displayImage);
    cv::imshow("Image", displayImage);
}

void Gui::drawBoundingBoxes(cv::Mat& image) const { // Draw bounding boxes on the image
    for (const auto& box : m_boundingBoxes) {
        cv::rectangle(image, cv::Rect(box.m_x, box.m_y, box.m_width, box.m_height), cv::Scalar(0, 255, 0), 2);
        cv::putText(image, box.m_label, cv::Point(box.m_x, box.m_y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
    }
}

void Gui::addBoundingBox(int x, int y, int width, int height, const std::string& label) { // Add a bounding box to be displayed
    m_boundingBoxes.push_back({x, y, width, height, label});
}

void Gui::waitForUserInput() const { // Wait for user input
    cv::waitKey(0);
}