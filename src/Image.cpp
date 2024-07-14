#include "Image.hpp"

Image::Image(const std::string& filePath) {
    m_image = cv::imread(filePath);
}

cv::Mat Image::getImage() const {
    return m_image;
}
