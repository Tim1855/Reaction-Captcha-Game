#include "Menu.hpp"
#include "Image.hpp"
#include "Gui.hpp"

int main() {
    std::string imagePath = "C:/appldev/Reaction-Captcha-Game/data/training/image_02/0000/000000.png"; 
    Image image(imagePath);

     if (!image.load()) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return -1;
    }

    //TEST IMAGE.HPP , GUI.HPP
    Gui gui; // Create Gui object    
    gui.initWindow(); // Initialize the GUI window    
    gui.showImage(image); // Display the image    
    gui.waitForUserInput(); // Wait for user input
    // Menu myMenu;
    // myMenu.displayMenu();
}