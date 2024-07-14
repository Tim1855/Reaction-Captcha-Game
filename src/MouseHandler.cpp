#include "MouseHandler.hpp"
#include <opencv2/opencv.hpp>

MouseHandler::MouseHandler() {
}

MouseHandler::~MouseHandler() {
}

void MouseHandler::setWindowName(const std::string& windowName) {
    this->windowName = windowName;
    cv::namedWindow(windowName); // Erstellen Sie das Fenster
    cv::setMouseCallback(windowName, mouseCallback, this); // Setzen Sie den Maus-Callback
}

void MouseHandler::setClickCallback(std::function<void(int, int)> callback) {
    clickCallback = callback;
}

void MouseHandler::mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        MouseHandler* self = static_cast<MouseHandler*>(userdata);
        if (self->clickCallback) {
            self->clickCallback(x, y);
        }
    }
}
