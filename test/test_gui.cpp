// #include "Image.hpp"
// #include "Gui.hpp"
// #include "BoundingBox.hpp"

// int main() {
//     std::string imagePath = "C:/appldev/Reaction-Captcha-Game/data/training/image_02/0000/000000.png";
//     std::string boundingBoxPath = "C:/appldev/Reaction-Captcha-Game/data/label_02/0000.txt";

//     // Create Image object
//     Image image(imagePath);

//     // Load the image
//     image.load();
//     image.checkLoad();

//     // Create BoundingBox object
//     BoundingBox boundingBox;

//     // Load the bounding boxes
//     boundingBox.loadBoundingBoxes(boundingBoxPath);
//     boundingBox.checkLoad();

//     // Create Gui object
//     Gui gui;

//     // Initialize the GUI window
//     gui.initWindow();

//     // Display the image with bounding boxes for frame 0
//     gui.showImage(image, boundingBox, 0);

//     // Wait for user input
//     gui.waitForUserInput();

//     return 0;
// }
