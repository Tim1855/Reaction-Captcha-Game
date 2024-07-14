// #include "MouseHandler.hpp"
// #include <opencv2/opencv.hpp>

// int main() {
//     cv::Mat image = cv::imread("C:/appldev/Reaction-Captcha-Game/data/training/image_02/0000/000000.png");
//     if (image.empty()) {
//         std::cerr << "Error: Image not found!" << std::endl;
//         return -1;
//     }

//     MouseHandler mouseHandler;
//     mouseHandler.setWindowName("Image Window");

//     mouseHandler.setClickCallback([](int x, int y) {
//         std::cout << "Mouse clicked at: (" << x << ", " << y << ")" << std::endl;
//     });

//     cv::imshow("Image Window", image);
//     cv::waitKey(0);

//     return 0;
// }
