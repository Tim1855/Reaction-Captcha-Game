#include "MouseHandler.hpp"
#include <opencv2/opencv.hpp>

void MouseHandler::onMouse(int event, int x, int y, int, void* param) {
    bool* clicked = static_cast<bool*>(param);
    if (event == cv::EVENT_LBUTTONDOWN) {
        *clicked = true;
    }
}
