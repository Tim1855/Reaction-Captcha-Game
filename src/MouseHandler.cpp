#include "MouseHandler.hpp"  
#include <opencv2/opencv.hpp>  

// Die statische Methode onMouse wird aufgerufen, wenn eine Mausaktion im zugeordneten OpenCV-Fenster stattfindet.
void MouseHandler::onMouse(int event, int x, int y, int, void* param) {
    // Umwandlung des void*-Zeigers in einen bool*-Zeiger, der angibt, ob ein Mausklick erfolgt ist
    bool* clicked = static_cast<bool*>(param);

    // Überprüfung, ob das Mausereignis ein Linksklick war
    if (event == cv::EVENT_LBUTTONDOWN) {
        *clicked = true;  // Setzt die clicked-Variable auf true, um den Klick zu registrieren
    }
}
