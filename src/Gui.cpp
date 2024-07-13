#include "Gui.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

// Constructor
Gui::Gui() {}

// Destructor
Gui::~Gui() {}

void Gui::initWindow() const {
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
}

void Gui::showImage(const Image& image, const BoundingBox& boundingBox, int frame) const {
    checkLoad(image, boundingBox);
    cv::Mat displayImage = image.getImage().clone();
    auto boxes = boundingBox.getBoundingBoxes(frame);
    if (boxes.empty()) {
        std::cerr << "No bounding boxes for frame " << frame << std::endl;
    } else {
        std::cout << "Displaying " << boxes.size() << " bounding boxes for frame " << frame << std::endl;
    }
    drawBoundingBoxes(displayImage, boxes);
    cv::imshow("Image", displayImage);
}


void Gui::drawBoundingBoxes(cv::Mat& image, const std::vector<BoundingBox::Box>& boundingBoxes) const {
    for (const auto& box : boundingBoxes) {
        cv::rectangle(image, cv::Rect(box.m_x, box.m_y, box.m_width, box.m_height), cv::Scalar(0, 255, 0), 2);
        cv::putText(image, box.m_label, cv::Point(box.m_x, box.m_y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
    }
}

void Gui::waitForUserInput() const {
    cv::waitKey(0);
}

void Gui::checkLoad(const Image& image, const BoundingBox& boundingBox) const {
    if (!image.isLoaded()) {
        std::cerr << "Image not loaded correctly." << std::endl;
        exit(-1);
    }
    if (!boundingBox.areLoaded()) {
        std::cerr << "Bounding boxes not loaded correctly." << std::endl;
        exit(-1);
    }
}
