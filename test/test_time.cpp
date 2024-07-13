// #include "MouseHandler.hpp"
// #include "TimeHandler.hpp"
// #include "GameHandler.hpp"
// #include <opencv2/opencv.hpp>
// #include <iostream>

// int main() {
//     // Initialisieren der Komponenten
//     MouseHandler mouseHandler;
//     TimeHandler timeHandler;
//     GameHandler gameHandler;

//     // Beispielbild laden
//     cv::Mat image = cv::imread("C:/appldev/Reaction-Captcha-Game/data/training/image_02/0000/000000.png");
//     if (image.empty()) {
//         std::cerr << "Error: Image not found!" << std::endl;
//         return -1;
//     }

//     // Maus-Callback einstellen
//     mouseHandler.setWindowName("Test Window");

//     mouseHandler.setClickCallback([](int x, int y) {
//         std::cout << "Mouse clicked at: (" << x << ", " << y << ")" << std::endl;
//     });

//     // Zeitmessung starten und stoppen
//     timeHandler.startTimer();
//     timeHandler.delay(2000); // 2 Sekunden Verzögerung
//     double elapsed = timeHandler.stopTimer();
//     std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;

//     // Spielinitialisierung
//     gameHandler.initializeGame("Player1", 5, 1, 1); // Beispielwerte

//     // Bild anzeigen und auf Mausklick warten
//     cv::imshow("Test Window", image);

//     // Spiel starten
//     gameHandler.startGame();

//     cv::waitKey(0);

//     return 0;
// }
