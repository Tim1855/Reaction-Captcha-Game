#ifndef GUI_HPP
#define GUI_HPP

#include "Image.hpp"
#include "BoundingBox.hpp"
#include <vector>
#include <string>

class Gui {
public:
    // Constructor
    Gui();

    // Destructor
    ~Gui();

    // Initialize the GUI window
    void initWindow() const;

    // Display the image
    void showImage(const Image& image, const BoundingBox& boundingBox, int frame) const;

    // Draw bounding boxes on the image
    void drawBoundingBoxes(cv::Mat& image, const std::vector<BoundingBox::Box>& boundingBoxes) const;

    // Wait for user input
    void waitForUserInput() const;

    // Verify that the image and bounding boxes are loaded and handle errors
    void checkLoad(const Image& image, const BoundingBox& boundingBox) const;
};

#endif // GUI_HPP
