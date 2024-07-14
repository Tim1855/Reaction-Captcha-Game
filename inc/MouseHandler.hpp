#ifndef MOUSEHANDLER_HPP
#define MOUSEHANDLER_HPP

#include <functional>
#include <string>

class MouseHandler {
public:
    MouseHandler();
    ~MouseHandler();

    void setClickCallback(std::function<void(int, int)> callback);
    void setWindowName(const std::string& windowName);

private:
    std::function<void(int, int)> clickCallback;
    std::string windowName;
    static void mouseCallback(int event, int x, int y, int flags, void* userdata);
};

#endif // MOUSEHANDLER_HPP
