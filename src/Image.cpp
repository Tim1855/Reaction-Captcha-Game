#include "Image.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// Constructor
Image::Image(const std::string& imagePath)
    : m_path(imagePath), m_loaded(false) {}

// Destructor
Image::~Image() {}

// Load the image from file
void Image::load() {
    m_image = cv::imread(m_path, cv::IMREAD_COLOR);
    m_loaded = !m_image.empty();
}

// Check if the image was loaded successfully
bool Image::isLoaded() const {
    return m_loaded;
}

// Verify the loaded image and handle errors
void Image::checkLoad() const {
    if (!isLoaded()) {
        std::cerr << "Failed to load image: " << m_path << std::endl;
        exit(-1);
    }
}

// Get the loaded image
const cv::Mat& Image::getImage() const {
    return m_image;
}

// Get the path of the image
const std::string& Image::getPath() const {
    return m_path;
}
