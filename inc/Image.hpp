#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <opencv2/opencv.hpp>

class Image {
public:
    // Constructor
    Image(const std::string& imagePath);

    // Destructor
    ~Image();

    // Load the image from file
    void load();

    // Check if the image was loaded successfully
    bool isLoaded() const;

    // Verify the loaded image and handle errors
    void checkLoad() const;

    // Get the loaded image
    const cv::Mat& getImage() const;

    // Get the path of the image
    const std::string& getPath() const;

private:
    std::string m_path;
    cv::Mat m_image;
    bool m_loaded;
};

#endif // IMAGE_HPP
