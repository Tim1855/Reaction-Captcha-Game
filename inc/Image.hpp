#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

class Image {
public:
    Image(const std::string& filePath);
    cv::Mat getImage() const;

private:
    cv::Mat m_image;
};

#endif // IMAGE_HPP
