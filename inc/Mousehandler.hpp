#ifndef MOUSEHANDLER_HPP
#define MOUSEHANDLER_HPP

#include <opencv2/opencv.hpp>

class MouseHandler {
public:
    static void onMouse(int event, int x, int y, int, void* param);

private:
    MouseHandler() = default;
};

#endif // MOUSEHANDLER_HPP
