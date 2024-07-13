/*

Darstellung und Interaktion

*/
#ifndef GUI_HPP
#define GUI_HPP

#include "Image.hpp"
#include <vector>
#include <string>

class Gui {
public:
  Gui(); // Constructor
  ~Gui(); // Destructor

  void initWindow() const; // Initialize the GUI window 

  void showImage(const Image& image) const;  // Display the image    

  void drawBoundingBoxes(cv::Mat& image) const; // Draw bounding boxes on the image   

  void addBoundingBox(int x, int y, int width, int height, const std::string& label); // Add a bounding box to be displayed 

  void waitForUserInput() const; // Wait for user input


private:
  struct BoundingBox {
        int m_x, m_y, m_width, m_height;
        std::string m_label;
    };
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif