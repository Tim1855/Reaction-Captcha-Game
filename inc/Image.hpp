/*
Laden und speichern von Bildern
*/

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <opencv2/opencv.hpp>

class Image {
public:
  Image(const std::string& imagePath); // Constructor
  ~Image();           // Destructor

  bool load();  // Load the image from file
  const cv::Mat& getImage() const;   // Get the loaded image
  const std::string& getPath() const;   // Get the path of the image

private:
  std::string m_path;
  cv::Mat m_image;

};


#endif