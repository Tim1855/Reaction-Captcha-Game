#include "Image.hpp"

Image::Image(const std::string& imagePath) // Constructor
    : m_path(imagePath) {}

Image::~Image() {} // Destructor

bool Image::load() { // Load the image from file
    m_image = cv::imread(m_path, cv::IMREAD_COLOR);
    if (m_image.empty()) {
        std::cerr << "Error: Could not load image at " << m_path << std::endl;
        return false;
    }
    return true;
}

const cv::Mat& Image::getImage() const { // Get the loaded image
    return m_image;
}

const std::string& Image::getPath() const { // Get the path of the image
    return m_path;
}